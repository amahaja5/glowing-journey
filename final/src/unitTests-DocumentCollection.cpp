/*
 * Unit test cases for DocumentCollection class.
 *
 * decided not to test the two output functions, as they 
 * were both void and simply printed the values of another 
 * function that we've used.
 *
 * Author: Avi Mahajan (amahaja5@jhu.edu)
 * Date Modified: 11/14/2016
 * Date Created: 11/14/2016
 */

#include "../include/catch.hpp" // simple unit-testing framework
#include "../include/DocumentCollection.hpp" // header declaring the functions we want to test
#include "../include/NgramCollection.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <limits>
using std::string;
using std::vector;
using std::list;

/*TEST_CASE("readNames", "[readNames]") {
    DocumentCollection d1(3);
    vector<std::string> v1{"file1.txt", "file2.txt", "file3.txt"};
    REQUIRE(d1.readNames("../test/sampleFileList.txt") == v1);
}*/

TEST_CASE("similarity of the same NgramCollection", "[similarity, buildNgrams]") {
    DocumentCollection d1(3);
    NgramCollection n1(3);
    vector<string> v1 {"I", "have", "a"};
    d1.buildNgrams(v1, "foo.bar");
    n1.increment(v1.begin(),v1.end());
    REQUIRE(d1.similarity(n1, n1) == std::numeric_limits<double>::infinity());
}

TEST_CASE("similiarity of dissimilar NgramCollections", "[similarity, buildNgrams]") {
    DocumentCollection d1(3);
    DocumentCollection d2(3);
    NgramCollection n1(3);
    NgramCollection n2(3);
    vector<string> v1 {"I", "have", "a"};
    vector<string> v2 {"dream", "that", "one"};
    vector<string> v3 {"day", "our", "children"};
    d1.buildNgrams(v1, "foo.bar");
    d2.buildNgrams(v2, "foo.bar");
    n1.increment(v3.begin(), v3.end());
    n2.increment(v2.begin(), v2.end()); 
    REQUIRE(d1.similarity(n1, n2) == 0.0);
    REQUIRE(d2.similarity(n1, n2) == 0.0);
}

TEST_CASE("similarity of moderately similar NgramCollections", "[similarity, buildNgrams]") {
    DocumentCollection d1(3);
    DocumentCollection d2(3);

    NgramCollection n1(3);
    NgramCollection n2(3);

    vector<string> v1 {"I", "have", "a"};
    vector<string> v2 {"dream", "that", "one"};
    vector<string> v3 {"day", "our", "children"};

    d1.buildNgrams(v1, "foo.bar");
    d1.buildNgrams(v2, "bar.foo");
    d1.buildNgrams(v3, "food.bar");

    d2.buildNgrams(v2, "foo.bar");

    n1.increment(v1.begin(), v1.end());
    n1.increment(v3.begin(), v3.end());

    n2.increment(v1.begin(), v1.end());
    n2.increment(v2.begin(), v2.end()); 

    REQUIRE(d1.similarity(n1, n2) != 0.0);
    REQUIRE(d1.similarity(n2, n1) == d1.similarity(n1, n2));
    REQUIRE(d2.similarity(n1, n2) != 0.0);
}


