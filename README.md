<div align='center'>

# EzTeX (WIP)

</div>

A concept for a sort of mathematical markdown language.
EzTeX will allow you to write mathematical expressions with intuitive plain text, and generate LaTeX code for you.

## What are TeX and LaTeX?

"LaTeX is the de facto standard for the communication and publication of scientific documents." - [latex-project.org](https://www.latex-project.org/)

- TeX: A powerful typesetting system created by Donald Knuth, used for producing documents with great care for typesetting specificity.
- LaTeX: A macro package built on top of TeX, making it easier to leverage the power of TeX.

## Why EzTeX?

Using the MSWord equation editor can be clumsy and learning a LaTeX system can be daunting.
EzTeX bridges the gap, allowing you to easily generate LaTeX code that can be copied and pasted into your favorite word processor for some nice-looking math.

Common word processors that support LaTeX:

- Microsoft Word
- MacOS Pages
- Google Docs

## Example use

### ***NOT YET IMPLEMENTED***, see [Development](#Development)

Some equations written in EzTeX:

Mass-energy equivalence: `` E = mc^2``

Definition of density: ``rho = m/V``

The quadratic equation: ``x = ( -b plusminus sqrt(b^2-4ac) ) / 2a``

The indefinite integral of sin(x) : ``integral sin x dx = cos x + C``

Sigma notation: ``Sigma_(i = m)^n a_i = a_m + a_(m+1) + ... + a_(n-1) + a_(n)``

The law of sines: `` sin(alpha)/alpha = sin(beta)/beta = sin(gamma)/gamma``

EzTeX is designed with simplicity in mind - no fancy syntax or keywords, just straight-forward plain text.

## Development

I am writing this for my friends who, in spite of my attempts at persuasion, see no need to learn LaTeX.
After all, their lab reports don't have *too* much math in them.

So far, we have a partial lexical analyzer and a partial translator ...
Together, they make a partial source-to-source compiler! (transpiler)

EzTeX can handle expressions void of parentheses and at most a single '/' character.
EzTeX can also recognize all characters of the greek alphabet
(excluding those characters with latin analogues e.g. A, B, E etc.).
