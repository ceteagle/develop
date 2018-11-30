#pragma once

#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/auxiliary/lazy.hpp>
#include <boost/spirit/home/support/terminal.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/fusion/include/at.hpp>

namespace boost {
    namespace spirit
    {
        // Our extended terminals
        BOOST_SPIRIT_DEFINE_TERMINALS_NAME_EX(
            (fixed_width, fixed_width_type)
        )

            ///////////////////////////////////////////////////////////////////////////
            // Enablers
            ///////////////////////////////////////////////////////////////////////////
            template <typename T>
        struct use_directive<qi::domain
            , terminal_ex<tag::fixed_width                     // enables fixed_width(exact)[p]
            , fusion::vector1<T> >
        > : mpl::true_ {};

        template <>                                         // enables *lazy* fixed_width(exact)[p]
        struct use_lazy_directive<
            qi::domain
            , tag::fixed_width
            , 1 // arity
        > : mpl::true_ {};
    }
}

namespace boost {
    namespace spirit {
        namespace qi
        {
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
            using spirit::fixed_width;
#endif
            using spirit::fixed_width_type;

            template <typename Subject, typename WidthType>
            struct fixed_width_parser : unary_parser<fixed_width_parser<Subject, WidthType> >
            {
                typedef Subject subject_type;
                fixed_width_parser(Subject const& subject_, WidthType const& width_)
                    : subject(subject_), width(width_) {}

                template <typename Context, typename Iterator>
                struct attribute
                {
                    typedef typename
                        traits::attribute_of<subject_type, Context, Iterator>::type
                        type;
                };

                template <typename Iterator, typename Context
                    , typename Skipper, typename Attribute>
                    bool parse(Iterator& first, Iterator const& last
                        , Context& context, Skipper const& skipper
                        , Attribute& attr_) const
                {
                    Iterator end = first + width;

                    if (last - first < width)
                        end = last;

                    if (subject.parse(first, end, context, skipper, attr_))
                    {
                        qi::skip_over(first, end, skipper);
                        return true;
                    }

                    return false;
                }

                template <typename Context>
                info what(Context& context) const
                {
                    return info("fixed_width", subject.what(context));
                }

                Subject     subject;
                WidthType   width;

            private:
                // silence MSVC warning C4512: assignment operator could not be generated
                fixed_width_parser & operator= (fixed_width_parser const&);
            };

            ///////////////////////////////////////////////////////////////////////////
            // Parser generators: make_xxx function (objects)
            ///////////////////////////////////////////////////////////////////////////
            template <typename T, typename Subject, typename Modifiers>
            struct make_directive<
                terminal_ex<tag::fixed_width, fusion::vector1<T> >, Subject, Modifiers>
            {
                typedef T width_type;
                typedef fixed_width_parser<Subject, width_type> result_type;

                template <typename Terminal>
                result_type operator()(
                    Terminal const& term, Subject const& subject, unused_type) const
                {
                    return result_type(subject, fusion::at_c<0>(term.args));
                }
            };
        }
    }
}

namespace boost {
    namespace spirit {
        namespace traits
        {
            ///////////////////////////////////////////////////////////////////////////
            template <typename Subject, typename WidthType>
            struct has_semantic_action<qi::fixed_width_parser<Subject, WidthType> >
                : unary_has_semantic_action<Subject> {};
        }
    }
}

