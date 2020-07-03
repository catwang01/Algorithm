import os
import re


def getItems():
    template = "{}. url: {} md: [Interview/{dir}]({dir})"
    output = []

    for file in os.listdir():
        # print(file)
        pattern = 'experience.*.md'
        ret = re.search(pattern, file)
        if ret is not None:
            with open(file)  as f:
                lines = f.read().split('\n')
                for i in range(len(lines)-1, -1, -1): 
                    ret = re.search("\[.*\]\(.*\)", lines[i])
                    if ret is not None:
                        output.append(template.format(len(output)+1, ret.group(), dir=file).replace('(1条未读通知) ', ''))
                        break
    return '\n\n'.join(output)

with open("readme.template") as f:
    template = f.read()

with open('readme.md', 'w') as f:
    text = template.replace("LIST", getItems())
    f.write(text)


