#pragma once

#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <vector>

struct SKIP_Actor
{
    void operator()(std::vector<char> const& attr, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) const
    {
#ifdef _DEBUG
        std::cout << "Skipped : ";
        for (std::vector<char>::const_iterator it = attr.begin(); it != attr.end(); ++it)
            std::cout << *it;
        std::cout << std::endl;
#endif
    }
};
