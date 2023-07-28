import unittest
import subprocess
import argparse

class TestMinishell(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        super(TestMinishell, self).__init__(*args, **kwargs)
        self.commands_to_test = []

    def run_command(self, shell, command):
        if shell == './minishell':
            process = subprocess.Popen(
                ['./minishell'],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                stdin=subprocess.PIPE,
                text=True
            )
            minishell_stdout, minishell_stderr = process.communicate(input=command)
            print(minishell_stdout, minishell_stderr)
            return minishell_stdout.strip(), minishell_stderr.strip()
        else:
            result = subprocess.run(
                [shell, '-c', command],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            return result.stdout.strip(), result.stderr.strip()


    def runTest(self):
        minishell_path = './minishell'
        bash_path = '/bin/bash'

        for command in self.commands_to_test:
            minishell_stdout, minishell_stderr = self.run_command(minishell_path, command)
            bash_stdout, bash_stderr = self.run_command(bash_path, command)

            self.assertEqual(minishell_stdout, bash_stdout, f"Output mismatch for command: {command}")
            self.assertEqual(minishell_stderr, bash_stderr, f"Error output mismatch for command: {command}")

def main(commands):
    suite = unittest.TestSuite()
    test_case = TestMinishell()
    test_case.commands_to_test = commands
    suite.addTest(test_case)
    runner = unittest.TextTestRunner()
    runner.run(suite)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Test minishell against bash for specific commands.')
    parser.add_argument('commands', metavar='command', type=str, nargs='+', help='a command to test')
    args = parser.parse_args()
    main(args.commands)

# https://github.com/Kwevan/42-Tests