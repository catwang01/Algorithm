import subprocess

def execute_cmd(cmd):
    completed_cmd = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE)
    return completed_cmd.stdout.decode().strip().split('\n')[0]

if __name__ == '__main__':
    path = '/Users/ed/Git/Algorithm/Leetcode'
    cmd = 'ls -t {path}'.format(path=path)
    
    description = execute_cmd(cmd)
    url = 'Leetcode/' + description.replace(' ', '%20')
    output = '|       | [{description}]({url}) |       |      |       |'.format(description = description, url = url)
    print(output)

    cmd = "echo '%s' | pbcopy"%output
    execute_cmd(cmd)
