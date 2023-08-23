# F*** Query Languages

A simple SQL Database

## Building

You can build FQL just like any other package: 
```bash
mkdir build
cd build
../configure
make
```

The resulting binary should be located at `build/src/fql`.

To install FQL, run `sudo make install`.

## Testing

FQL relies on its own test suite rather than on the one provided by GNU Autotools.

To run the automated test suite:

 - Compile FQL as per the [instructions above](#Building).
 - Make sure you have `bundle` installed.
 - Make sure you have the `rspec` Gem installed.
 - Execute the following command in the root directory of this repo:
```bash
bundle exec rspec
```

Tests are written in Ruby, and are located in the `spec` directory.

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Before opening a pull request, please run `./format` to format your code to fit this project's code style.

## License

![GPL3 License](https://www.gnu.org/graphics/gplv3-with-text-136x68.png)

FQL is licensed under the GPLv3 license, which you can find [here](COPYING).