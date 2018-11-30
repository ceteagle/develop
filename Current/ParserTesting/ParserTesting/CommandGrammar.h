#pragma once

#include <boost/spirit/include/qi.hpp>
#include "qi_extensions.hpp"
#include <vector>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

namespace CommandGrammar
{
    // Command parser attribute type
#define T0 std::vector<char>
#define T1 std::vector< boost::variant<int, double, std::vector<char> > >
#define T2 boost::optional<std::vector<char> >
    typedef boost::fusion::vector3< T0, T1, T2 > CommandAttrType;
    typedef boost::fusion::vector3< T0, T1, T2 > ContinueAttrType;

    template<typename Actor>
    struct ResizeFieldVectorActor
    {
        ResizeFieldVectorActor(Actor& actor, size_t size) : command_a(actor), size_i(size) {}

        void operator()(CommandAttrType const& attr, qi::unused_type, qi::unused_type) const
        {
            const size_t size = boost::fusion::at_c<1>(attr).size();
            if (size < size_i)
                const_cast<T1&>(boost::fusion::at_c<1>(attr)).resize(size_i, std::vector<char>());
            else if ((size % size_i) != 0)
                const_cast<T1&>(boost::fusion::at_c<1>(attr)).resize((size / size_i)*size_i + size_i, std::vector<char>());
            command_a.operator()(attr, qi::unused_type(), qi::unused_type());
        }

        // Actors
        Actor& command_a;

        size_t size_i;
    };

#undef T0 
#undef T1 
#undef T2

    //! Command grammar 
    template <typename Iterator, typename Actor>
    struct small_field_command_grammar : public qi::grammar<Iterator, ascii::blank_type>
    {
        small_field_command_grammar(Actor& actor) : small_field_command_grammar::base_type(start_r), command_a(actor)
        {
            using qi::fixed_width;
            using ascii::alnum;
            using qi::char_;
            using qi::int_;
            using qi::double_;
            using qi::real_parser;
            using qi::strict_real_policies;
            using qi::eol;
            using qi::repeat;
            using qi::omit;
            using qi::no_skip;

            name_r = fixed_width(8)[+alnum];                                                                                    // Read alphanumeric command name
            field_r = fixed_width(8)[real_parser<double, strict_real_policies<double> >() | int_ | *(char_ - eol)];           // Read characters except eol
            continue_r = fixed_width(8)[omit[no_skip[char_ - eol]] >> *(char_ - eol)];                                              // Read column 10 fields (2-8) 
            skip_r = *(char_ - eol) >> eol;

            start_r = (name_r >> repeat(1, 8)[field_r] >> -continue_r >> skip_r)[command_a];
        }

        // Rules
        qi::rule<Iterator, std::vector<char>(), ascii::blank_type>                                  name_r;
        qi::rule<Iterator, boost::variant<int, double, std::vector<char> >(), ascii::blank_type>	field_r;
        qi::rule<Iterator, std::vector<char>(), ascii::blank_type>	                                continue_r;

        qi::rule<Iterator, ascii::blank_type>                                                       start_r;
        qi::rule<Iterator, ascii::blank_type>                                                       skip_r;

        // Actors
        Actor&                      														        command_a;
    };

    //! continue grammar 
    template <typename Iterator, typename Actor>
    struct small_field_continue_grammar : public qi::grammar<Iterator, ascii::blank_type>
    {
        small_field_continue_grammar(Actor& actor) : small_field_continue_grammar::base_type(start_r), command_a(actor)
        {
            using qi::fixed_width;
            using ascii::alnum;
            using qi::char_;
            using qi::int_;
            using qi::double_;
            using qi::real_parser;
            using qi::strict_real_policies;
            using qi::lit;
            using qi::eol;
            using qi::eoi;
            using qi::attr;
            using qi::repeat;
            using qi::omit;
            using qi::no_skip;

            name_r = fixed_width(8)[(no_skip[lit('+')] >> *(char_ - eol)) | (eoi >> attr(std::vector<char>()))];                      // Read alphanumeric command name
            field_r = fixed_width(8)[real_parser<double, strict_real_policies<double> >() | int_ | *(char_ - eol)];               // Read characters except eol
            continue_r = fixed_width(8)[omit[no_skip[char_ - eol]] >> *(char_ - eol)];                                                  // Read column 10 fields (2-8) 
            skip_r = *(char_ - eol) >> eol;

            start_r = (name_r >> repeat(1, 8)[field_r] >> -continue_r >> skip_r)[command_a];
        }

        // Rules
        qi::rule<Iterator, std::vector<char>(), ascii::blank_type>                                  name_r;
        qi::rule<Iterator, boost::variant<int, double, std::vector<char> >(), ascii::blank_type>	field_r;
        qi::rule<Iterator, std::vector<char>(), ascii::blank_type>	                                continue_r;

        qi::rule<Iterator, ascii::blank_type>                                                       start_r;
        qi::rule<Iterator, ascii::blank_type>                                                       skip_r;

        // Actors
        Actor&                      														        command_a;
    };

    //! Command grammar 
    template <typename Iterator, typename Actor>
    struct command_grammar : public qi::grammar<Iterator, ascii::blank_type>
    {
        command_grammar(Actor& actor) : command_grammar::base_type(start_r), small_field_g(actor)
        {
            start_r = small_field_g;
        }

        // Rules
        qi::rule<Iterator, ascii::blank_type>                           start_r;

        // Grammar
        small_field_command_grammar<Iterator, Actor>                    small_field_g;
    };

    //! continue grammar 
    template <typename Iterator, typename Actor>
    struct continue_grammar : public qi::grammar<Iterator, ascii::blank_type>
    {
        continue_grammar(Actor& actor) : continue_grammar::base_type(start_r), small_field_g(actor)
        {
            start_r = small_field_g;
        }

        // Rules
        qi::rule<Iterator, ascii::blank_type>                           start_r;

        // Grammar
        small_field_continue_grammar<Iterator, Actor>                    small_field_g;
    };

    template <typename Iterator, typename CommandActor>
    struct skip_grammar : public qi::grammar<Iterator, ascii::blank_type>
    {
        skip_grammar(CommandActor& actor) : skip_grammar::base_type(start_r), command_a(actor)
        {
            using qi::char_;
            using qi::eol;

            start_r = (*(char_ - eol) >> eol)[command_a];
        }

        // Rules
        qi::rule<Iterator, ascii::blank_type> start_r;

        // Actors
        CommandActor&           command_a;
    };
}


