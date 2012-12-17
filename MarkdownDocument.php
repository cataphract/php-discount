<?php
/**
 * Discount PHP extension.
 *
 * This extension is a wrapper for the discount library, written by David
 * Parsons.
 *
 * This a file with dummy definitions written in order to generate the
 * documentation.
 *
 * @copyright 2012 Gustavo Lopes (extension), David Parsons (library)
 * @package Discount
 * @link http://pecl.php.net/markdown Project homepage
 * @link http://cataphract.github.com/php-discount/ Git development repository
 * @link http://www.pell.portland.or.us/~orc/kbd/discount/ Discount library
 */

/**
 * A class that represents a document written the markdown markup language,
 * allowing it to be converted into an HTML document.
 *
 * Simple typical usage has the form (full examples linked below):
 * {@example simple_usage.php 25 3}
 *
 * Unless otherwise noted, all the methods:
 * <ul>
 * <li>Return <var>FALSE</var> if there is a wrong number of arguments or if
 * the type of the argument is unexpected and PHP does not provide an automatic
 * conversion to the required type.</li>
 * <li>Throw <var>LogicException</var> if the method is an instance method and,
 * except for {@link MarkdownDocument::initFromStream()} and
 * {@link MarkdownDocument::initFromString()}, is used without the document
 * having been initialized. This can only happen in subclasses whose constructor
 * doesn't call either {@link MarkdownDocument::initFromStream()} or
 * {@link MarkdownDocument::initFromString()} (or calls to them fail but the
 * constructor doesn't abort the object construction with an exception).</li>
 * <li>Throw <var>LogicException</var> if the method is called from within a
 * callback provided to {@link MarkdownDocument::setUrlCallback()} or
 * {@link MarkdownDocument::setAttributeCallback()}.</li>
 * <li>Throw <var>LogicException</var> if the method requires the Markdown
 * document to be compiled, but it isn't (or not to be compiled, but it
 * is).</li>
 * </ul>
 *
 * The methods that take a stream can instead take a URL from which such
 * stream can be opened, but beware that if the method is to write a result,
 * the stream will be opened with mode <var>'w'</var>, most likely discarding
 * the previous contents of the file.
 *
 * Explaining the Markdown syntax is beyond the scope of this documentation.
 * For that purpose, you can consult the
 * {@link http://daringfireball.net/projects/markdown/syntax syntax of the
 * original Markdown}. Discount also implements
 * {@link http://www.pell.portland.or.us/~orc/Code/discount/#Language.extensions
 * several extensions}, which you can deactivate with great granularity by using
 * the flags described in this document.
 *
 * @package Discount
 * @author Gustavo Lopes
 * @example simple_usage.php A simple example of the usage of this class.
 * @example subclassing.php Simple subclassing to simplify usage.
 * @example subclassing_2.php Subclassing example with table of contents & CSS.
 * @link http://pecl.php.net/markdown Project homepage
 * @link http://cataphract.github.com/php-discount/ Git development repository
 * @link http://www.pell.portland.or.us/~orc/kbd/discount/ Discount library
 * @since 0.1.0
 */
class MarkdownDocument {
	/**
	 * A compile flag that disables processing the markdown elements that would
	 * otherwise create HTML links (like in
	 * <kbd>[text](http://www.example.com)</kbd>);
	 * additionally, it escapes any <kbd>A</kbd> (anchor) element it finds.
	 * @var int Compile flag to forbid links (HTML anchors).
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @see MarkdownDocument::SAFELINK
	 * @see MarkdownDocument::NO_EXT
	 * @see MarkdownDocument::AUTOLINK
	 * @since 0.1.0
	 */
	const NOLINKS			= 1;

	/**
	 * A compile flag that disables processing the markdown elements that would
	 * otherwise create HTML images (like in
	 * <kbd>![alt text](http://www.example.com/myimg.jpg "title")</kbd>);
	 * additionally, it escapes any <kbd>IMG</kbd> element it finds.
	 * @var int Compile flag to forbid images (HTML img element)
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @since 0.1.0
	 */
	const NOIMAGE			= 2;

	/**
	 * A compile flag that deactivates smartypants substitutions such as turning
	 * <kbd>(tm)</kbd> into <kbd>&trade;</kbd>, <kbd>don't</kbd> into
	 * <kbd>don&rsquo;t</kbd>, among others (see the example).
	 * @var int Compile flag to deactivate smartypants substitutions.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @link http://daringfireball.net/projects/smartypants/ Page for original
	 * SmartyPants project
	 * @example smartypants.php Smartypants-style substitutions in action
	 * @since 0.1.0
	 */
	const NOPANTS			= 4;

	/**
	 * A compile flag that disables all literal HTML present in the input by
	 * encoding all the tags.
	 * @var int Compile flag to deactivate literal HTML.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @since 0.1.0
	 */
	const NOHTML			= 8;

	/**
	 * A compile flags that has the effects of approximating the behavior of
	 * discount to that of the original Markdown, by disabling several
	 * extensions.
	 *
	 * In particular, it has the effect of combining
	 * {@link MarkdownDocument::NOSUPERSCRIPT},
	 * {@link MarkdownDocument::NORELAXED},
	 * {@link MarkdownDocument::NOSTRIKETHROUGH},
	 * {@link MarkdownDocument::NODLIST},
	 * {@link MarkdownDocument::NOALPHALIST},
	 * {@link MarkdownDocument::NODIVQUOTE} and,
	 * {@link MarkdownDocument::NOTABLES}, 
	 * @var into Compile flag to disable most discount extensions and
	 * increase compatibility with the original Markdown.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @since 0.1.0
	 */
	const STRICT			= 16;

	/**
	 * A compile flag that aims to process attribute-safe fragments.
	 *
	 * This flag disables <kbd>[]</kbd> expansion for images or links,
	 * (including literal HTML for them) smarty pants, ticks, autolink (even
	 * with {@link MarkdownDocument::AUTOLINK}), emphasis; it also transforms >
	 * into &gt; and " into &quote;. Its purpose is to transform text
	 * that could go into tag attributes. Best used with
	 * {@link MarkdownDocument::transformFragment()} or
	 * {@link MarkdownDocument::writeFragment()}, as many substitutions done
	 * by {@link MarkdownDocument::compile()} +
	 * {@link MarkdownDocument::getHtml()} are not covered.
	 * @var int Flag to make fragments more attribute-safe.
	 * @see MarkdownDocument::transformFragment()
	 * @since 0.1.0
	 */
	const TAGTEXT			= 32;

	/**
	 * A compile flag that disables the use of pseudo-protocols for links.
	 * Pseudo-protocols are link protocols that result in HTML elements other
	 * than anchors being generated. They are a discount extension. See the
	 * example for more details.
	 *
	 * @var int Compile flag to disable the use of pseudo-protocols.
	 * @example pseudoprotos.php Pseudo-protocols in action.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @see MarkdownDocument::NOLINKS
	 * @see MarkdownDocument::SAFELINK
	 * @since 0.1.0
	 */
	const NO_EXT			= 64;

	/**
	 * A compile flag that, for {@link MarkdownDocument::writeFragment()} and
	 * {@link MarkdownDocument::writeHtml()}, causes any <kbd>< </kbd>,
	 * <kbd> ></kbd>, <kbd>&</kbd>, <kbd>"</kbd> and <kbd>'</kbd> characters
	 * in the final output to be converted to their corresponding XML entities.
	 *
	 * @var int Compile flag to enable conversion into basic XML entities.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::writeHtml()
	 * @see MarkdownDocument::writeFragment()
	 * @since 0.1.0
	 */
	const CDATA				= 128;

	/**
	 * A compile flag that deactivates the conversion of superscripts expressed
	 * with <kbd>^</kdb>, as in <kbd>A^B</kdd> or <kbd>A^(BC)</kbd> (a discount
	 * extension).
	 *
	 * <kbd>SUP</kbd> tags can still be included literally (but see
	 * {@link MarkdownDocument::NOHTML}).
	 *
	 * @var int Compile flag to disable superscripts.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @see MarkdownDocument::STRICT
	 * @since 0.1.0
	 */
	const NOSUPERSCRIPT		= 256;

	/**
	 * A compile flag that forces discount to substitute with EM elements all
	 * the pairs of underscores it finds. In normal circumstances, discount will
	 * ignore underscores that are surrounded by alphanumeric characters.
	 *
	 * For instance, this flag forces emphasis in <kbd>c d</kbd> for the input
	 * string <kbd>ab_c d_2</kbd>, which would otherwise not happen.
	 *
	 * The "relaxed" parsing of underscores is a discount extension borrowed
	 * from Markdown extra; this flag forces compliant behavior.
	 *
	 * @var int Compile flag to disable relaxed parsing of underscores.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @see MarkdownDocument::STRICT
	 * @link http://michelf.com/projects/php-markdown/extra/#em Markdown extra
	 * description of the relaxed emphasis rules.
	 * @since 0.1.0
	 */
	const NORELAXED			= 512;

	/**
	 * A compile flag that disables the parsing of tables. Tables are a discount
	 * extension borrowed by Markdown Extra.
	 *
	 * Tables can still be written with literal HTML (but see
	 * {@link MarkdownDocument::NOHTML}).
	 *
	 * @var int Compile flag to deactivate Markdown Extra tables.
	 * @see MarkdownDocument::STRICT
	 * @see MarkdownDocument::compile()
	 * @link http://michelf.com/projects/php-markdown/extra/#table Syntax for
	 * Markdown Extra tables.
	 * @since 0.1.0
	 */
	const NOTABLES			= 1024;

	/**
	 * A compile flag that deactivates the conversion of striken-through text,
	 * as in <kbd>~~text~~</kbd>, to be converted to <kbd><del>text</del></kbd>.
	 * This conversion is a discount extension.
	 *
	 * The <kbd>DEL</kbd> element can still be introduced with literal HTML
	 * (but see {@link MarkdownDocument::NOHTML}).
	 *
	 * @var int Compile flag to disable strike-through.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @see MarkdownDocument::STRICT
	 * @since 0.1.0
	 */
	const NOSTRIKETHROUGH	= 2048;

	/**
	 * A compile flag that forces a table of contents to be generated and the
	 * headings to have attributed an id.
	 *
	 * The generated table of contents can then be retrieved with
	 * {@link MarkdownDocument::getToc()} or written with
	 * {@link MarkdownDocument::writeToc()}.
	 *
	 * @var int Compile flag to activate table of contents generation.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::getToc()
	 * @see MarkdownDocument::writeToc()
	 * @since 0.1.0
	 */
	const TOC				= 4096;

	/**
	 * A compile flag that applies some compatibility quirks in order to force
	 * discount passing some compatibility tests.
	 *
	 * Particularly, it makes:
	 * <ol>
	 * <li>the first line of every block has trailing whitespace trimmed
	 * off;</li>
	 * <li>require second [] for links/images instead of using label as key in
	 * the absence of it;</li>
	 * <li>more lax algorithm if content of []() link/image starts with <.</li>
	 * </ol>
	 *
	 * @var int Compile flag to turn on compatibility quirks.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @since 0.1.0
	 */
	const ONE_COMPAT		= 8192;

	/**
	 * A compile flag that turns every found URL into a link.
	 *
	 * In general, for a URL to linkified, it needs < and > around it. This flag
	 * drops that requirement and linkifies all the recognized URLs.
	 *
	 * @var int Compile flag to linkify every URL.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @see MarkdownDocument::NOLINKS
	 * @since 0.1.0
	 */
	const AUTOLINK			= 16384;

	/**
	 * A compile flag that limits generated links to certain protocols.
	 *
	 * The allowed protocols are <var>http</var>, <var>https</var>,
	 * <var>news</var> and <var>ftp</var>. Links starting with <var>/</var>, but
	 * not relative links, are also allowed.
	 *
	 * Pseudo-protocols are also deactivated, there is no need to include
	 * {@link MarkdownDocument::NO_EXT}.
	 *
	 * Links with arbitrary destinations are still allowed with literal HTML,
	 * but see {@link MarkdownDocument::NOHTML}.
	 *
	 * @var int Compile flag to generate links only for some protocols.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::transformFragment()
	 * @see MarkdownDocument::NOLINKS
	 * @see MarkdownDocument::NO_EXT
	 * @since 0.1.0
	 */
	const SAFELINK			= 32768;

	/**
	 * An input flag that deactivates parsing of pandoc-style headers.
	 *
	 * Note that Markdown does not currently support multi-line headers.
	 *
	 * @var int Input flag to process pandoc-style headers.
	 * @see MarkdownDocument::createFromString()
	 * @see MarkdownDocument::createFromStream()
	 * @see MarkdownDocument::initFromStream()
	 * @see MarkdownDocument::initFromString()
	 * @example pandoc_headers.php Pandoc headers in action.
	 * @link http://johnmacfarlane.net/pandoc/README.html#title-blocks
	 * Documentation on pandoc-style headers.
	 * @since 0.1.0
	 */
	const NOHEADER			= 65536;

	/**
	 * An input flag to treat tab stops as 4 spaces � has no effect unless the
	 * extension was compiled with a different tab stop.
	 *
	 * The default tab stop is 4 spaces, so this flag usually has no effect.
	 *
	 * @var int Input flag to force tab stops to be 4 spaces longs, even when
	 * discount was compiled otherwise.
	 * @since 0.1.0
	 */
	const TABSTOP			= 131072;

	/**
	 * Compile flag that deactivates turning certain special block quotes into
	 * <kbd>DIV</kbd> elements with a certain class.
	 *
	 * In discount, blockquotes whose first line has the form
	 * <kbd> > %classname%</kbd> will be transformed into a <kbd>DIV</kbd>
	 * element with the indicated class instead of a <kbd>BLOCKQUOTE</kbd>
	 * element. This is a discount extension that can be deactivated with this
	 * class.
	 *
	 * @var int Compile flag to deactivate turning certain quoted blocks into
	 * <kbd>DIV</kbd> elements with an arbitrary class.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::STRICT
	 * @since 0.1.0
	 */
	const NODIVQUOTE		= 262144;

	/**
	 * Compile flag that deactivates alphabetically ordered lists. These lists
	 * are a discount extension.
	 *
	 * @var int Compile flag to deactivate alphabetically ordered lists.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::STRICT
	 * @since 0.1.0
	 */
	const NOALPHALIST		= 524288;

	/**
	 * Compile flag that deactivates definition lists, either discount-style or
	 * Markdown-extra style.
	 *
	 * @var int Compile flag to deactivate definition lists. These lists are a
	 * discount extension.
	 *
	 * @see MarkdownDocument::STRICT
	 * @see MarkdownDocument::compile()
	 * @example definition_list.php Definitions list and NODLIST.
	 * @since 0.1.0
	 */
	const NODLIST			= 1048576;

	/**
	 * A combination of the compile flags {@link MarkdownDocument::NOLINKS},
	 * {@link MarkdownDocument::NOIMAGE} and {@link MarkdownDocument::TAGTEXT}.
	 * Effectively, the same effect as {@link MarkdownDocument::TAGTEXT}.
	 *
	 * It's unclear why discount includes this flag since the effects of
	 * {@link MarkdownDocument::NOLINKS} and {@link MarkdownDocument::NOIMAGE}
	 * are included in those of {@link MarkdownDocument::TAGTEXT}.
	 *
	 * @var int Combination of compile flags with the same effect as
	 * {@link MarkdownDocument::TAGTEXT}.
	 * @see MarkdownDocument::transformFragment()
	 * @see MarkdownDocument::TAGTEXT
	 * @see MarkdownDocument::NOIMAGE
	 * @see MarkdownDocument::NOLINKS
	 * @since 0.1.0
	 */
	const EMBED				= 35;

	/**
	 * Compile flag that enables the use of PHP Markdown Extra-style footnotes.
	 * 
	 * @var int Compile flag that enables footnotes. Footnotes are a discount
	 * extension borrowed from Markdown Extra.
	 * 
	 * @link http://michelf.com/projects/php-markdown/extra/#footnotes Syntax
	 * for Markdown Extra footnotes
	 * @see MarkdownDocument::compile()
	 * @since 1.0.0
	 */
	const EXTRA_FOOTNOTE	= 2097152;

	/**
	 * Compile flag that disables the processing of &lt;style> sections (for inclusion
	 * in the return of {@link MarkdownDocument::getCss()}). It has no effect if
	 * {@link MarkdownDocument:NOHTML} is already enabled.
	 *
	 * @var int Bit for disabling processing &lt;style> sections.
	 * @see MarkdownDocument::NOHTML
	 * @see MarkdownDocument::getCss()
	 * @since 1.1.0
	 */
	const NOSTYLE			= 4194304;

	/**
	 * Creates a {@link MarkdownDocument} from a stream.
	 * 
	 * This is one of the two public methods available for creating an object of
	 * this type, which is required as an initial step for full markdown
	 * processing.
	 * 
	 * @param mixed $markdown_stream Either a stream resource opened with
	 * reading permissions or a URL from which such a stream can be opened.
	 * @param integer $flags Data input type flags. Only the flags
	 * {@link MarkdownDocument::NOHEADER} and {@link MarkdownDocument::TABSTOP}
	 * are allowed.
	 * @return MarkdownDocument An object of the type of this class, created
	 * from data read from the specified stream.
	 * @see MarkdownDocument::createFromString()
	 * @see MarkdownDocument::initFromStream()
	 * @since 0.1.0
	 */
	static public function createFromStream($markdown_stream, $flags = 0) {}

	/**
	 * Creates a {@link MarkdownDocument} from a string.
	 * 
	 * This is one of the two public methods available for creating an object of
	 * this type, which is required as an initial step for full markdown
	 * processing.
	 * 
	 * @param mixed $markdown_doc A string containing the document expressed
	 * in the markdown markup language.
	 * @param integer $flags Data input type flags. Only the flags
	 * {@link MarkdownDocument::NOHEADER} and {@link MarkdownDocument::TABSTOP}
	 * are allowed.
	 * @return MarkdownDocument An object of the type of this class, created
	 * from data read from the specified string.
	 * @see MarkdownDocument::createFromStream()
	 * @see MarkdownDocument::initFromString()
	 * @since 0.1.0
	 */
	static public function createFromString($markdown_doc, $flags = 0) {}

	/**
	 * Reads markdown from a string and transforms it to HTML without creating
	 * any block elements.
	 * 
	 * In this form (inline markdown), the transformations made are much more
	 * limited than with the combination of
	 * {@link MarkdownDocument::createFromString()},
	 * {@link MarkdownDocument::compile()} and
	 * {@link MarkdownDocument::getHtml()}. No paragraph tags are added and no
	 * tables, block quotes, code blocks, pandoc headers or reference-style
	 * links/images or lists are processed.
	 * 
	 * Arbitrary HTML is still allowed, unless the
	 * {@link MarkdownDocument::NOHTML} flag is given.
	 * 
	 * @param string $markdown_fragment The markdown fragment to convert.
	 * @param integer $flags Compile flags appropriate for inline markdown
	 * (several features are disabled in inline markdown, so many flags have
	 * no effect).
	 * @return string A string with the HTML resulting from transforming the
	 * markdown fragment.
	 * @see MarkdownDocument::writeFragment()
	 * @since 0.1.0
	 */
	static public function transformFragment($markdown_fragment, $flags = 0) {}
	
	/**
	 * Reads markdown from a string, transforms it to HTML without creating
	 * any block elements and writes the result to a stream.
	 * 
	 * In this form (inline markdown), the transformations made are much more
	 * limited than with the combination of
	 * {@link MarkdownDocument::createFromString()},
	 * {@link MarkdownDocument::compile()} and
	 * {@link MarkdownDocument::writeHtml()}. No paragraph tags are added and no
	 * tables, block quotes, code blocks, pandoc headers or reference-style
	 * links/images or lists are processed.
	 * 
	 * Arbitrary HTML is still allowed, unless the
	 * {@link MarkdownDocument::NOHTML} flag is given.
	 * 
	 * @param string $markdown_fragment The markdown fragment to convert.
	 * @param mixed $out_stream A resource stream that can be written to or a
	 * URL with which a stream with writing permissions can be opened.
	 * @param integer $flags Compile flags appropriate for inline markdown
	 * (several features are disabled in inline markdown, so many flags have
	 * no effect).
	 * @return boolean <var>TRUE</var> if all the data is successfully written;
	 * if there is an error when writing to the stream, <var>FALSE</var> is
	 * returned and a warning is raised. The usual error handling for
	 * {@link MarkdownDocument} objects still apply.
	 * @see MarkdownDocument::transformFragment()
	 * @since 0.1.0
	 */
	static public function writeFragment($markdown_fragment, $out_stream, $flags = 0) {}

	/**
	 * A no-op protected constructor.
	 * 
	 * This method prevents instantiation of the {@link MarkdownDocument}
	 * class with <var>new</var>, forcing the usage of
	 * {@link MarkdownDocument::createFromString()} or
	 * {@link MarkdownDocument::createFromStream()}.
	 * 
	 * It is protected to, nevertheless, allow subclassing in a straightforward
	 * manner by overriding this constructor. The overriding constructor need
	 * not call this method, as it is a no-op. It should, however, call either
	 * the {@link MarkdownDocument::initFromString()} or
	 * {@link MarkdownDocument::initFromStream()}.
	 * 
	 * @see MarkdownDocument::createFromString()
	 * @see MarkdownDocument::createFromStream()
	 * @see MarkdownDocument::initFromString()
	 * @see MarkdownDocument::initFromStream()
	 * @since 0.1.0
	 */
	protected function __construct() {}
	
	/**
	 * Initialize the native part of the object using an input stream.
	 * 
	 * This method reads markdown data from the passed stream and initializes
	 * the native discount data structure. It should be called in the
	 * constructor of subclasses; if not, it should at least be called before
	 * any of the {@link MarkdownDocument} methods be called. Alternatively,
	 * {@link MarkdownDocument::initFromString()} can be called instead.
	 * 
	 * @param mixed $markdown_stream Either a stream resource opened with
	 * reading permissions or a URL from which such a stream can be opened.
	 * @param integer $flags Data input type flags. Only the flags
	 * {@link MarkdownDocument::NOHEADER} and {@link MarkdownDocument::TABSTOP}
	 * are allowed.
	 * @return boolean <var>TRUE</var> unless one of the usual error
	 * conditions for the {@link MarkdownDocument} class is triggered.
	 * @throws LogicException If the object has already been initialized.
	 * @see MarkdownDocument::initFromString()
	 * @see MarkdownDocument::createFromStream()
	 * @since 0.1.0
	 */
	final protected function initFromStream ($markdown_stream, $flags = 0) {}
	
	/**
	 * Initialize the native part of the object using a string.
	 * 
	 * This method reads markdown data from the passed string and initializes
	 * the native discount data structure. It should be called in the
	 * constructor of subclasses; if not, it should at least be called before
	 * any of the {@link MarkdownDocument} methods be called. Alternatively,
	 * {@link MarkdownDocument::initFromStream()} can be called instead.
	 * 
	 * @param mixed $markdown_doc Either a stream resource opened with
	 * reading permissions or a URL from which such a stream can be opened.
	 * @param integer $flags Data input type flags. Only the flags
	 * {@link MarkdownDocument::NOHEADER} and {@link MarkdownDocument::TABSTOP}
	 * are allowed.
	 * @return boolean <var>TRUE</var> unless one of the usual error
	 * conditions for the {@link MarkdownDocument} class is triggered.
	 * @throws LogicException if the object has already been initialized.
	 * @see MarkdownDocument::initFromString()
	 * @since 0.1.0
	 */
	final protected function initFromString($markdown_doc, $flags = 0) {}

	/**
	 * Compiles this document, preparing the HTML data to be retrieved.
	 *
	 *
	 * @param integer $flags A combination of the compile flags, i.e., all but
	 * {@link MarkdownDocument::NOHEADER} and {@link MarkdownDocument::TABSTOP}.
	 * @return boolean <var>TRUE</var> unless one of the usual error
	 * conditions for the {@link MarkdownDocument} class is triggered.
	 * @throws LogicException if the object has already been compiled.
	 * @since 0.1.0
	 *
	 */
	public function compile($flags) {}
	
	/**
	 * Tells whether this document has already been compiled.
	 * 
	 * This method will return <var>TRUE</var> if
	 * {@link MarkdownDocument::compile()} has already been successfully called
	 * and <var>FALSE</var> otherwise.
	 * 
	 * @return boolean Whether the document has already been compiled.
	 * @see MarkdownDocument::compile()
	 * @since 0.1.0
	 */
	public function isCompiled() {}
	
	/**
	 * Write an outline view of the document.
	 * 
	 * @param mixed $out_stream A resource stream opened with write permissions
	 * or a URL that can be opened to yield such a stream, for writing the
	 * output.
	 * @param string $title A string to be prefixed to the tree.
	 * @return boolean Returns <var>TRUE</var>, except for the situations covered
	 * in the class summary.
	 * @example dump_tree.php dumpTree() in action.
	 * @since 0.1.0
	 */
	public function dumpTree($out_stream, $title = "") {}
	
	/**
	 * The title found in the pandoc-style header.
	 * 
	 * Note that discount does not currently support multi-line titles.
	 *
	 * The document need not have been compiled.
	 * 
	 * @example pandoc_headers.php getTitle() in action.
	 * @link http://johnmacfarlane.net/pandoc/README.html#title-blocks
	 * Documentation on pandoc-style headers.
	 * @return string The title found in the pandoc-style header. An empty
	 * string is returned if no title was found or if
	 * {@link MarkdownDocument::NOHEADER} was used.
	 * @see MarkdownDocument::getAuthor()
	 * @see MarkdownDocument::getDate()
	 * @see MarkdownDocument::NOHEADER
	 * @since 0.1.0
	 */
	public function getTitle() {}
	
	/**
	 * The author or authors found in the pandoc-style hader.
	 *
	 * Note that discount does not currently support multi-line authors.
	 *
	 * The document need not have been compiled.
	 *
	 * @link http://johnmacfarlane.net/pandoc/README.html#title-blocks
	 * Documentation on pandoc-style headers.
	 * @return string The authors found in the pandoc-style header. An empty
	 * string is returned if no authors were found or if
	 * {@link MarkdownDocument::NOHEADER} was used.
	 * @see MarkdownDocument::getTitle()
	 * @see MarkdownDocument::getDate()
	 * @see MarkdownDocument::NOHEADER
	 * @since 0.1.0
	 */
	public function getAuthor() {}
	
	/**
	 * The date found in the pandoc-style header.
	 *
	 * The document need not have been compiled.
	 *
	 * @link http://johnmacfarlane.net/pandoc/README.html#title-blocks
	 * Documentation on pandoc-style headers.
	 * @return string The date found in the pandoc-style header. An empty
	 * string is returned if no date was found or if
	 * {@link MarkdownDocument::NOHEADER} was used.
	 * @see MarkdownDocument::getTitle()
	 * @see MarkdownDocument::getAuthor()
	 * @see MarkdownDocument::NOHEADER
	 * @since 0.1.0
	 */
	public function getDate() {}

	/**
	 * Generate and return the body HTML data that results from processing this
	 * document.
	 *
	 * This includes all the data present in the given markup with the exception
	 * of the pandoc-style headers and the style blocks. The unprocessed headers
	 * will, however, show up if {@link MarkdownDocument::NOHEADER} is given,
	 * and the escaped style blocks will show up if
	 * {@link MarkdownDocument::NOHTML} is given.
	 * 
	 * The document should already have been compiled.
	 *
	 * If defined, this method calls the callbacks specified through
	 * {@link MarkdownDocument::setUrlCallback()} and
	 * {@link MarkdownDocument::setAttributesCallback()} for each link
	 * generated. If any of these callbacks throws an exception, this method
	 * throws another exception on top of it on the first time.
	 * 
	 * @return string The body of the final HTML that results from processing
	 * this document.
	 * @see MarkdownDocument::writeHtml()
	 * @see MarkdownDocument::writeXhtmlPage()
	 * @see MarkdownDocument::transformFragment()
	 * @since 0.1.0
	 */
	public function getHtml() {}


	/**
	 * Writes the HTML contents of the body of the processed markup document.
	 * 
	 * This includes all the data present in the given markup with the exception
	 * of the pandoc-style headers and the style blocks. The unprocessed headers
	 * will, however, show up if {@link MarkdownDocument::NOHEADER} is given,
	 * and the escaped style blocks will show up if
	 * {@link MarkdownDocument::NOHTML} is given.
	 *
	 * The document should already have been compiled.
	 *
	 * If defined, this method calls the callbacks specified through
	 * {@link MarkdownDocument::setUrlCallback()} and
	 * {@link MarkdownDocument::setAttributesCallback()} for each link
	 * generated. If any of these callbacks throws an exception, this method
	 * throws another exception on top of it on the first time.
	 *
	 * @param mixed $markdown_outstream A resource stream opened with write
	 * permissions or a URL that can be opened to yield such a stream, for
	 * writing the output.
	 * @return boolean <var>TRUE</var> on normal conditions or
	 * <var>FALSE</var> and raises a warning if there was an I/O error when
	 * writing to the given stream (or to a successfully opened stream, if a URL
	 * was provided instead). The usual error handling described in the class
	 * synopsis still applies.
	 * @see MarkdownDocument::compile()
	 * @see MarkdownDocument::getHtml()
	 * @see MarkdownDocument::writeCss()
	 * @see MarkdownDocument::writeXhtmlPage()
	 * @since 0.1.0
	 */
	public function writeHtml($markdown_outstream) {}

	/**
	 * Writes a complete XHTML page.
	 *
	 * The style blocks found in the markdown data are put in the
	 * <kbd>HEAD</kbd> element, the <kbd>TITLE</kbd> element is built from the
	 * title extracted from the pandoc-style header and the
	 * <kbd>BODY</kbd> is composed by what
	 * {@link MarkdownDocument::writeHtml()} would return.
	 *
	 * The document should already have been compiled.
	 *
	 * @param mixed $markdown_outstream A resource stream opened with write
	 * permissions or a URL that can be opened to yield such a stream.
	 * @return boolean <var>TRUE</var> on normal conditions or
	 * <var>FALSE</var> and raises a warning if there was an I/O error when
	 * writing to the given stream or to a successfully opened stream, if a URL
	 * was provided instead.
	 * @see MarkdownDocument::writeHtml()
	 * @see MarkdownDocument::writeCss()
	 * @see MarkdownDocument::getTitle()
	 * @since 0.1.0
	 */
	public function writeXhtmlPage($markdown_outstream) {}
	
	/**
	 * Returns the table of contents HTML data.
	 *
	 * This method must be called after the document has been compiled with
	 * {@link MarkdownDocument::TOC}.
	 *
	 * @return string the table of contents HTML data or <var>FALSE</var> if
	 * {@link MarkdownDocument::TOC} was not given to
	 * {@link MarkdownDocument::compile()}.
	 * @see MarkdownDocument::TOC
	 * @since 0.1.0
	 */
	public function getToc() {}
	
	/**
	 * Give all the <kbd><style></kbd> elements found in the
	 * markdown document. These elements will not be included in the result
	 * returned by {@link MarkdownDocument::getHtml()}.
	 * 
	 * This function returns an empty string if the flag
	 * {@link MarkdownDocument::NOHTML} was specified.
	 * 
	 * The markdown document must have already been compiled.
	 * 
	 * @return string All the <kbd><style></kbd> elements found in the
	 * markdown document.
	 * @see MarkdownDocument::writeCss()
	 * @since 0.1.0
	 */
	public function getCss() {}

	/**
	 * Writes the table of contents HTML data into a file.
	 *
	 * This method must be called after the document has been compiled with
	 * {@link MarkdownDocument::TOC}.
	 *
	 * @param mixed $markdown_outstream A stream resource where the HTML table
	 * of contents can be written or a URL that can be opened for writing.
	 * @return boolean <var>TRUE</var> if the table of contents was built and
	 * successfully written; <var>FALSE</var> if
	 * {@link MarkdownDocument::TOC} was not given or if writing failed, in the
	 * last case, a warning is also raised. The usual handling of the errror
	 * conditions described in the introduction to the {@link MarkdownDocument}
	 * class still apply.
	 * @see MarkdownDocument::TOC
	 * @since 0.1.0
	 */
	public function writeToc($markdown_outstream) {}

	/**
	 * Writes all the <kbd><style></kbd> elements found in the
	 * markdown document. These elements will not be included in the result
	 * returned by {@link MarkdownDocument::getHtml()} or written by
	 * {@link MarkdownDocument::writeHtml()}.
	 * 
	 * This function returns an empty string if the flag
	 * {@link MarkdownDocument::NOHTML} was specified.
	 * 
	 * The markdown document must have already been compiled.
	 *
	 * @param mixed $markdown_outstream A stream resource where the style
	 * elements can be written or a URL that can be opened for writing.
	 * @return boolean <var>TRUE</var> on normal conditions or
	 * <var>FALSE</var> and raises a warning if there was an I/O error when
	 * writing to the given stream (or to a successfully opened stream, if a URL
	 * was provided instead). The usual error handling described in the class
	 * synopsis also applies.
	 * @see MarkdownDocument::getCss()
	 * @since 0.1.0
	 */
	public function writeCss($markdown_outstream) {}

	/**
	 * Sets a callback to replace the URLs in generated links.
	 * 
	 * The callback refers to a function that will receive one argument, a
	 * string with the URL that would be included with a generated link and
	 * returns either a replacement URL that will be used instead or
	 * <var>NULL</var>, to use the original URLs.
	 * 
	 * Links that were written as literal HTML in the input will <b>not</b> be
	 * passed to the callback!
	 * 
	 * The object need not have been compiled before this function is called.
	 * 
	 * The actual URL conversion and calling of the callback happens when
	 * {@link MarkdownDocument::getHtml()} or
	 * {@link MarkdownDocument::writeHtml()} are called.
	 *
	 * @return boolean Returns <var>TRUE</var>, except for the situations
	 * covered in the class summary.
	 * @param callback $callback Callback function to replace URLs. Receives
	 * a string and should return either a string or NULL. This parameter can be
	 * <var>NULL</var> to remove the callback.
	 * @see MarkdownDocument::setAttributesCallback()
	 * @since 0.1.0
	 */
	public function setUrlCallback($callback) {}
		
	/**
	 * Sets a callback to add attributes to <kbd>A</kbd> elements in generated
	 * links.
	 * 
	 * The callback refers to a function that will receive one argument, a
	 * string with the URL that would be included with a generated link and
	 * returns either a string with the attributes and their values, to be
	 * appended to the generated <kbd>A</kbd> element or <var>NULL</var>, which
	 * has the same effect as an empty string and causes no extra attributes to
	 * be appended.
	 * 
	 * Links that were written as literal HTML in the input will <b>not</b>
	 * cause the callback to be called!
	 * 
	 * The object need not have been compiled before this function is called.
	 * 
	 * The actual URL conversion and calling of the callback happens when
	 * {@link MarkdownDocument::getHtml()} or
	 * {@link MarkdownDocument::writeHtml()} are called.
	 *
	 * @return boolean Returns <var>TRUE</var>, except for the situations
	 * covered in the class summary.
	 * @param callback $callback Callback function to add attributes to links.
	 * Receives a string and should return either a string or NULL. This
	 * parameter can be <var>NULL</var> to remove the callback.
	 * @see MarkdownDocument::setUrlCallback()
	 * @since 0.1.0
	 */
	public function setAttributesCallback($callback) {}


	/**
	 * This function allows customizing the prefix used in footnote references.
	 * More specifically, it changes the <kbd>name</kbd> attributes of the
	 * anchors from <kbd>fn:N</kbd> and <kbd>fnref:N</kbd> to
	 * <kbd>{$prefix}:N</kbd> and <kbd>{$prefix}ref:N</kbd>. This allows, for
	 * instance, for displaying several articles rendered individually in the
	 * same page without clashes in the footnote links.
	 * 
	 * This function can only be called if the document has not yet been
	 * compiled.
	 * 
	 * Usage of footnotes requires the {@link MarkdownDocument::EXTRA_FOOTNOTE}
	 * compile flag.
	 * 
	 * @return boolean Returns <var>TRUE</var>, except for the situations
	 * covered in the class summary.
	 * @param string $prefix The prefix to use.
	 * @see MarkdownDocument::EXTRA_FOOTNOTE
	 * @see MarkdownDocument::compile()
	 * @since 1.0.0
	 */
	public function setReferencePrefix($prefix) {}
}

