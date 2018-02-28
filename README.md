## *Experimental. Not yet published.*

![humble by Eliricon from the Noun Project](https://github.com/f34nk/modest_ex/blob/master/modest_icon.png)

# ModestEx

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

	iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
	{:ok, "<a>Hello</a>"}

*Right now you can only clone the repo and execute tests...*

https://github.com/f34nk/modest_ex/blob/master/test

https://github.com/f34nk/modest_ex/blob/master/target/modest_client/test

## Supported CSS Selectors

All common CSS Selectors are supported. For an extensive list please [check out this table](https://github.com/f34nk/modest_ex/blob/master/SELECTORS.md).

## Installation

	git clone git@github.com:f34nk/modest_ex.git
	cd modest_ex

<!-- If [available in Hex](https://hex.pm/docs/publish), the package can be installed
by adding `gumbo_query_ex` to your list of dependencies in `mix.exs`:

```elixir
def deps do
  [
    {:modest_ex, "~> 0.1.0"}
  ]
end
```

Documentation can be generated with [ExDoc](https://github.com/elixir-lang/ex_doc)
and published on [HexDocs](https://hexdocs.pm). Once published, the docs can
be found at [https://hexdocs.pm/gumbo_query_ex](https://hexdocs.pm/gumbo_query_ex).
 -->

## Update submodules

All binding targets are added as submodules in the `target/` folder.

	git submodule update --init --recursive --remote

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
	mix test.target

## Cleanup

	mix clean

## Benchmark

	mix bench

## Roadmap

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
	- [ ] Parse a HTML-document into a tree
	- [ ] Expose node-retrieval functions
- [x] List of supported CSS Selectors
- [ ] Documentation
- [ ] Publish as hex package

## License

ModestEx is under LGPL license. Check the [LICENSE](https://github.com/f34nk/modest_ex/blob/master/LICENSE) file for more details.


## Icon Credit

humble by Eliricon from the Noun Project