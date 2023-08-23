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
		IO.popen("./build/src/fqlconsole", "r+") do |pipe|
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

		expected = "fql> Error: Table full."

		result = run_script(script)
		expect(result[-2]).to eq(expected)
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
end