#include <iostream>

#include "boost/spirit/include/qi.hpp"
#include "qi_extensions.hpp"

#include "Parser.h"
#include "CommandsRepository.h"
#include "CommandsContainer.h"
#include "CommandGrammar.h"
#include "COMMAND_Actor.hpp"
#include "CONTINUE_Actor.hpp"
#include "SKIP_Actor.hpp"

using namespace boost::spirit;

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    ///////////////////////////////////////////////////////////////////////////
    //  Our number list compiler
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, std::vector<double>& v)
    {
        using qi::double_;
        using qi::phrase_parse;
        using qi::_1;
        using ascii::space;

        bool r = phrase_parse(first, last,

            //  Begin grammar
            (
                double_ % ','
                )
            ,
            //  End grammar

            space, v);

        if (first != last) // fail if we did not get a full match
            return false;
        return r;
    }

    template <typename Iterator>
    bool parse_command(Iterator first, Iterator last)
    {
        //using qi::fixed_width;
        //using ascii::alnum;
        //using qi::char_;
        //using qi::int_;
        //using qi::double_;
        //using qi::real_parser;
        //using qi::nastran_strict_real_policies;
        //using qi::eol;
        //using qi::repeat;
        //using qi::omit;
        //using qi::no_skip;

        ///*
        //CASE_Actor          case_actor(nasContainer, *m_pDatabaseHelper);
        //INCLUDE_Actor       include_actor(*m_pDatabaseHelper);
        //
        //COMMENT_Actor       comment_actor;
        //*/

        //COMMAND_Actor       command_actor(nasContainer, *m_pDatabaseHelper);
        //CONTINUE_Actor      continue_actor(nasContainer, *m_pDatabaseHelper);
        //SKIP_Actor          skip_actor;

        //nas_grammar<
        //    const char*,
        //    COMMAND_Actor,
        //    CONTINUE_Actor,
        //    SKIP_Actor
        //>
        //    nas_g(
        //        comment_actor,
        //        case_actor,
        //        include_actor,
        //        command_actor,
        //        continue_actor,
        //        skip_actor
        //    );
        //  

        ////qi::rule<Iterator, ascii::blank_type> start_r;

        //auto name_r = fixed_width(8)[+alnum];                                                                                    // Read alphanumeric command name
        //auto field_r = fixed_width(8)[real_parser<double, nastran_strict_real_policies<double> >() | int_ | *(char_ - eol)];           // Read characters except eol
        //auto continue_r = fixed_width(8)[omit[no_skip[char_ - eol]] >> *(char_ - eol)];                                              // Read column 10 fields (2-8) 
        //auto skip_r = *(char_ - eol) >> eol;

        //auto r = phrase_parse(first, last, (name_r >> repeat(1, 8)[field_r] >> -continue_r >> skip_r)[command_a], boost::spirit::ascii::blank);
        //if (r && first != last)
        //{
        //    r = parse_command_continue(first, last);
        //}
        //    


        ////auto start_r = (name_r >> repeat(1, 8)[field_r] >> -continue_r >> skip_r)[command_a];

        ////bool r = phrase_parse(first, last, start_r, boost::spirit::ascii::blank);
        //
        //return r;
        return false;
    }

    template <typename Iterator>
    bool parse_command_continue(Iterator first, Iterator last)
    {
        //using qi::fixed_width;
        //using ascii::alnum;
        //using qi::char_;
        //using qi::int_;
        //using qi::double_;
        //using qi::real_parser;
        //using qi::nastran_strict_real_policies;
        //using qi::eol;
        //using qi::repeat;
        //using qi::omit;
        //using qi::no_skip;

        //auto name_r = fixed_width(8)[(no_skip[lit('+')] >> *(char_ - eol)) | (eoi >> attr(std::vector<char>()))];                      // Read alphanumeric command name
        //auto field_r = fixed_width(8)[real_parser<double, nastran_strict_real_policies<double> >() | int_ | *(char_ - eol)];               // Read characters except eol
        //auto continue_r = fixed_width(8)[omit[no_skip[char_ - eol]] >> *(char_ - eol)];                                                  // Read column 10 fields (2-8) 
        //auto skip_r = *(char_ - eol) >> eol;
        //// Actors
       
        //CommandGrammar::command_grammar <Iterator, COMMAND_Actor>   command_g;

        //auto r = phrase_parse(first, last, (name_r >> repeat(1, 8)[field_r] >> -continue_r >> skip_r)[command_g], boost::spirit::ascii::blank);
        //if (r && first != last)
        //{
        //    r = parse_command_continue(first, last);
        //}



        ////auto start_r = (name_r >> repeat(1, 8)[field_r] >> -continue_r >> skip_r)[command_a];

        ////bool r = phrase_parse(first, last, start_r, boost::spirit::ascii::blank);

        //return r;
        return false;
    }
}


int main()
{
    std::cout << "MAIN" << std::endl;

    std::string cmd = "\
PCOMP   123     -0.224  11.1    22.2    HILL    44.4    55.5    SYM\r\n\
+       1       77.7    88.8    YES     ";


    CommandsRepository repo;
    Parser parser;
    if (parser.Parse(cmd.c_str(), cmd.size(), &repo, nullptr) != 0)
    {
        std::cout << "FAIL!" << std::endl;
        return 1;
    }











    return 0;

    if (client::parse_command(cmd.begin(), cmd.end()))
    {
        std::cout << "Success!" << std::endl;
    }
    

    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tA comma separated list parser for Spirit...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout << "Give me a comma separated list of numbers.\n";
    std::cout << "The numbers will be inserted in a vector of numbers\n";
    std::cout << "Type [q or Q] to quit\n\n";

    std::string str;
    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        std::vector<double> v;
        if (client::parse_numbers(str.begin(), str.end(), v))
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << str << " Parses OK: " << std::endl;

            for (std::vector<double>::size_type i = 0; i < v.size(); ++i)
                std::cout << i << ": " << v[i] << std::endl;

            std::cout << "\n-------------------------\n";
        }
        else
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}