#
# FQL
# Copyright (C) 2023 Jozef Nagy
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#

 describe 'database' do
	def run_script(commands)
		raw_output = nil
		IO.popen("./build/src/fqlconsole test.db", "r+") do |pipe|
			commands.each do |command|
				pipe.puts command
			end
			pipe.close_write
			raw_output = pipe.gets(nil)
		end
		raw_output.split("\n")
	  end

	it 'inserts and retrieves a row' do
		result = run_script([
			"insert 1 test foo@bar.com",
			"select",
			".exit",])
		expect(result).to match_array([
			"OK.",
			"fql> ",
			"fql> (1, test, foo@bar.com)",
			"fql> OK.",])
	end

	it 'prints error message when table is full' do
		script = (1..1401).map do |i|
			"insert #{i} user#{i} foo#{i}@bar.com"
		end
		script << ".exit"

		result = run_script(script)
		expect(result[-2]).to eq("fql> Error: Table full.")
	end

	it 'prints error message if strings are too long' do
		long_uname = "a" * 33
		long_email = "a" * 256
		script = [
			"insert 1 #{long_uname} #{long_email}",
			"select",
			".exit",
		]

		result = run_script(script)
		expect(result).to match_array([
			"fql> ",
			"fql> OK.",
			"fql> String is too long.",
		])
	end

	it 'allows inserting strings that are the maximum length' do
		long_uname = "a" * 32
		long_email = "b" * 255

		script = [
			"insert 1 #{long_uname} #{long_email}",
			"select",
			".exit",
		]
		result = run_script(script)
		expect(result).to match_array([
			"OK.",
			"fql> ",
			"fql> (1, #{long_uname}, #{long_email})",
			"fql> OK.",
		])
	end

	it 'prints an error message if ID is negative' do
		script = [
			"insert -1 test foo@bar.com",
			"select",
			".exit",
		]
		result = run_script(script)
		expect(result).to match_array([
			"fql> ID must be positive.",
			"fql> OK.",
			"fql> ",
		])
	end

	it 'keeps data after closing the connection' do
		result1 = run_script([
			"insert 1 test foo@bar.com",
			".exit",
		])
		expect(result1).to match_array([
			"fql> OK.",
			"fql> ",
		])

		result2 = run_script([
			"select",
			".exit",
		])
		expect(result2).to match_array([
			"fql> (1, test, foo@bar.com)",
			"OK.",
			"fql> ",
		])
	end

	after do
		`rm -rf test.db`
	end
end