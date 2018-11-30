#pragma once
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include "COMMAND_Actor.hpp"
#include "CONTINUE_Actor.hpp"
#include "SKIP_Actor.hpp"

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template
<
    typename Iterator,
    typename COMMAND_Actor,
    typename CONTINUE_Actor,
    typename SKIP_Actor
>
struct Grammar : public qi::grammar<Iterator, ascii::blank_type>
{
    Grammar(COMMAND_Actor   &command_actor,
        CONTINUE_Actor  &continue_actor,
        SKIP_Actor      &skip_actor)
        : Grammar::base_type(start_r),
        command_g(command_actor),
        continue_g(continue_actor),
        skip_g(skip_actor)
    {
        start_r = +(command_g | continue_g | skip_g);
    }

    // Rules
    qi::rule<Iterator, ascii::blank_type                                                        >   start_r;

    // Grammars
    CommandGrammar::skip_grammar            <Iterator, SKIP_Actor                           >   skip_g;
    CommandGrammar::command_grammar         <Iterator, COMMAND_Actor                        >   command_g;
    CommandGrammar::continue_grammar        <Iterator, CONTINUE_Actor                       >   continue_g;
};
