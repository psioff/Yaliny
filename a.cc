/*
    the yaliny's test
    written by Andrew Khorolsky

    compile: g++ a.cc -std=c++11 -Wall
    note: i suppose that "Lorick/Loririck/Loriharick" are different names of single man, not a brothers names.
    todo: replace hardcoded fix-tables with generated ones

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>


int main (int argc, char *argv[]) {
     if(argc < 2) {
         std::cerr << "usage: " << argv[0] << " <input file>\n";
         return 1;
     }

    std::ifstream is;
    is.open(argv[1]);

    std::string male_suffix[] = {
	"fan",
	"grim",
	"hik",
	"jin",
	"ner",
	"rick",
	"ser",
	"ston",
	"tix",
	"tor",
	"wor"
    };
    std::string female_suffix[] = {
	"la",
	"na",
	"ni",
	"ra",
	"sa"
    };
    std::string prefix[] = {
	"bil",
	"cal",
	"car",
	"dav",
	"el",
	"fel",
	"hel",
	"hes",
	"kas",
	"lil",
	"lo",
	"min",
	"nes",
	"o",
	"pa",
	"re",
	"ron",
	"um",
	"ven",
	"xar",
	"xas"
    };
    std::set<std::string> name;

    while(!is.eof()) { // input data
	std::string l;
        is >> l;
	// normalize data and check for duplicates
	std::transform(l.begin(), l.end(), l.begin(), ::tolower);
        if(!l.empty()) {
	    std::string _suffix;
	    for(auto &m: male_suffix) {
		if(l.rfind(m) == (l.size() - m.size())) {
		    _suffix = m;
		    break;
		}
	    }
	    for(auto &f: female_suffix) {	// u should check 4 nonempty m_suf before
		if(l.rfind(f) == (l.size() - f.size())) {
		    _suffix = f;
		    break;
		}
	    }
	    std::string _prefix;
	    for(auto &p: prefix) {
		if(l.substr(0, p.size()) == p) {
		    _prefix = p;
		    break;
		}
	    }
	    if(!_suffix.empty() && !_prefix.empty()) {
		name.insert(_prefix+_suffix);
	    }
	}
    }
    is.close();

    std::set<std::string> m_suffix;
    std::set<std::string> f_suffix;
    std::set<std::string> _prefix;

    for(auto &n: name) {	// acounting number of suffixes and prefixes
	for(auto &m: male_suffix) {
	    if(n.rfind(m) == (n.size() - m.size())) {
		m_suffix.insert(m);
	    }
	}
	for(auto &f: female_suffix) {
	    if(n.rfind(f) == (n.size() - f.size())) {
		f_suffix.insert(f);
	    }
	}
	for(auto &p: prefix) {
	    if(n.substr(0, p.size()) == p) {
		_prefix.insert(p);
	    }
	}
    }
    // nearest generation with garanteed common parent
    size_t min_suffix_size = std::min(m_suffix.size(), f_suffix.size());
    double generation = std::ceil(std::log2((2.*min_suffix_size*_prefix.size()/name.size() + 1)) - 1);
    std::cout << generation << "\n";	// how about zero? should i test "gen" for a negative value or i'll get zero-gen automatically?
    return 0;
}
