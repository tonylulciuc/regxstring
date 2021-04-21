//#include <boost/regex.hpp>

#include <pcre.h>
#include <vector>
#include <fstream>
#include <gtest/gtest.h>
#include "../include/regxstring.h"

using namespace std;

static pcre *pcre_compile_DZ(const string &regx)
{
    const char *error;
    int erroffset;
    pcre *re = pcre_compile(
        regx.c_str(),
        0,
        &error,
        &erroffset,
        0);
    if (!re)
        cerr << "error at offset " << erroffset << ": " << error << "\n\n";
    return re;
}

static bool pcre_exec_DZ(const string &str, pcre *re)
{
    const int size = 120;
    vector<int> ovector(size);
    pcre_extra extra;
    extra.flags = PCRE_EXTRA_MATCH_LIMIT;
    extra.match_limit = 200000000;
    int rc = pcre_exec(
        re,              /* the compiled pattern */
        &extra,          /* no extra data - we didn't study the pattern */
        str.c_str(),     /* the subject string */
        (int)str.size(), /* the length of the subject */
        0,               /* start at offset 0 in the subject */
        0,               /* default options */
        &ovector[0],     /* output vector for substring information */
        size);           /* number of elements in the output vector */
    if (rc < 0)
    {
        switch (rc)
        {
        case PCRE_ERROR_NOMATCH:
            break;
            // Handle other special cases if you like
        default:
            cerr << "Matching error " << rc << " :\n";
            break;
        }
        return false;
    }
    return true;
}

static string Trim(string str){
    size_t i = 0,e = str.length();
    for(;i < e && isspace(str[i]);++i);
    size_t j = e;
    for(;j > i && isspace(str[j - 1]);--j);
    return (i < j ? str.substr(i,j - i) : "");
}

static string pre_handle(const string & str)
{
    string ret = Trim(str);
    if(!ret.empty()){
        if(ret[0] != '^')
            ret.insert(ret.begin(),'^');
        if(ret[ret.size() - 1] != '$')
            ret.push_back('$');
    }
    return ret;
}


namespace {
    TEST(CRegxStringTest, parseRegex_can_generate_string_from_regex) {
        const int TOTAL_NUMBER_OR_RAND_STRINGS = 10;
        ifstream testInput;
        CRegxString regxstr;
        string regx;

        testInput.open("resource/test_input.txt");
        EXPECT_TRUE(testInput.is_open());

        
        while (getline(testInput, regx))
        {
            regx = pre_handle(regx);
            pcre *re = pcre_compile_DZ(regx);
            EXPECT_TRUE(re);

            regxstr.ParseRegx(regx.c_str());

            for (int i = 0; i < TOTAL_NUMBER_OR_RAND_STRINGS; ++i) {
                regxstr.RandString();
                const string &str = regxstr.LastString();
                EXPECT_TRUE(pcre_exec_DZ(str, re));
            }
            
            pcre_free(re);
        }

        testInput.close();
        EXPECT_FALSE(testInput.is_open());
    }
}
