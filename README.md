## *Under development.*

![humble by Eliricon from the Noun Project](https://github.com/f34nk/modest_ex/blob/master/modest_icon.png)

# ModestEx

A library to do pipeable transformations on html strings with CSS selectors, e.g. find(), prepend(), append(), replace() etc.

Elixir/Erlang bindings for lexborisovs **Modest**

>Modest is a fast HTML renderer implemented as a pure C99 library with no outside dependencies.

- [Modest](https://github.com/lexborisov/Modest)
	- HTML5 parsing library in pure C99
	- fully conformant with the HTML5 spec

The binding is implemented as a **C-Node** following the excellent example in [@Overbryd](https://github.com/Overbryd/nodex) package **nodex**. If you want to learn how to set up bindings to C/C++, you should definitely check it out.

- [nodex](https://github.com/Overbryd/nodex)
	- distributed Elixir
	- save binding with C-Nodes

>C-Nodes are external os-processes that communicate with the Erlang VM through erlang messaging. That way you can implement native code and call into it from Elixir in a safe predictable way. The Erlang VM stays unaffected by crashes of the external process.

## Example

[Full list of features.](https://github.com/f34nk/modest_ex/blob/master/FEATURES.md)

	iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
	{:ok, "<a>Hello</a>"}
	
	iex> ModestEx.serialize("<div>Hello<span>World")
	{:ok, "<html><head></head><body><div>Hello<span>World</span></div></body></html>"}

## Supported CSS Selectors

All common CSS Selectors are supported. For an extensive list please [check out this table](https://github.com/f34nk/modest_ex/blob/master/SELECTORS.md).

## Installation

Available on [hex](https://hex.pm/packages/modest_ex) and [hexdocs](https://hexdocs.pm/modest_ex/ModestEx.html).

```elixir
def deps do
  [
    {:modest_ex, "~> 0.0.1-dev"}
  ]
end
```

## Target dependencies

	cmake 3.x
	erlang-dev
	erlang-xmerl
	erlang-parsetools
<!--
	libtool (GNU libtool) 2.x
	g++ version 5.x -->

## Compile and test

	mix deps.get
	mix compile
	mix test

## Cleanup

	mix clean

## Benchmark

	mix bench

## Cloning

	git clone git@github.com:f34nk/modest_ex.git
	cd modest_ex

All binding targets are added as submodules in the `target/` folder.

	git submodule update --init --recursive --remote
	mix deps.get
	mix compile
	mix test
	mix test.target
	
## Roadmap

See [CHANGELOG](https://github.com/f34nk/modest_ex/blob/master/CHANGELOG.md).

- [ ] Bindings
	- [x] Call as C-Node
	- [ ] Call as dirty-nif
- [ ] Tests
	- [x] Call as C-Node
	- [ ] Call as dirty-nif
	- [x] Target tests
	- [x] Feature tests
	- [ ] Package test
- [ ] Features
	- [x] Find nodes using a CSS selector
	- [x] Serialize any string with valid or broken html
	- [ ] Remove a node from html
	- [ ] Append node to another node
	- [ ] Prepend node to another node
	- [ ] Replace node with another node
	- [ ] Slice html to a subset of nodes
- [x] List of supported CSS Selectors
- [ ] Documentation
- [ ] Publish as hex package

## License

ModestEx is under LGPL license. Check the [LICENSE](https://github.com/f34nk/modest_ex/blob/master/LICENSE) file for more details.


## Icon Credit

humble by Eliricon from the Noun Project