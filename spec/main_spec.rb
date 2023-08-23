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
			# Two "fql>"'s for insert and select - I might
			# look into stripping the prompt someday
			"fql> fql> (1, test, foo@bar.com)",
			"fql> ",])
	end
end