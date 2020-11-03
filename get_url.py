import subprocess
import requests
import os
import sys

current_root = os.path.dirname(__file__)

def execute_cmd(cmd):
    completed_cmd = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE)
    return completed_cmd.stdout.decode().strip().split('\n')[0]


def get_headers(raw_headers):
    """
    通过原生请求头获取请求头字典
    :param raw_headers: {str} 浏览器请求头
    :return: {dict} headers
    """
    raw_headers = raw_headers.strip()  # 处理可能的空字符
    raw_headers = raw_headers.split("\n")  # 分割每行
    raw_headers = [line.split(":", 1) for line in raw_headers]  # 分割冒号
    raw_headers = dict((k.strip(), v.strip()) for k, v in raw_headers)  # 处理可能的空字符
    return raw_headers

def getLink(output):

    raw_headers = """
    :authority: cn.bing.com
    :method: GET
    :scheme: https
    accept-encoding: gzip, deflate, br
    accept-language: zh-CN,zh;q=0.9,en;q=0.8
    cache-control: no-cache
    cookie: DUP=Q=bXttrPRrJkpeRKY-ZL6tlQ2&T=388384042&A=2&IG=A8738C3D2D284AB3B1A7CA01568CE6D1; _EDGE_V=1; MUID=1E6789D821716BB72C398755205F6A42; SRCHD=AF=NOFORM; SRCHUID=V=2&GUID=2C7BCADF53554408AC885C1AAE12E92A&dmnchg=1; MUIDB=1E6789D821716BB72C398755205F6A42; _EDGE_S=mkt=zh-cn&SID=20CE32AAB11D6C70014D3C06B0336D72; SRCHS=PC=U316; _TTSS_IN=hist=WyJ6aC1IYW5zIiwiZW4iLCJhdXRvLWRldGVjdCJd; _tarLang=default=en; _TTSS_OUT=hist=WyJlcyIsInpoLUhhbnMiLCJlbiJd; ULC=P=A4EC|11:2&H=A4EC|11:2&T=A4EC|11:2:1; ENSEARCH=BENVER=0; _clarity=79c533f56f9144bea047adccd8970e67; ABDEF=V=0&ABDV=0&MRNB=1587810161196&MRB=0; _SS=SID=20CE32AAB11D6C70014D3C06B0336D72&bIm=51:897&PC=U316; SRCHUSR=DOB=20200314&T=1588037015000; ipv6=hit=1588040617252&t=4; SNRHOP=I=&TS=; SRCHHPGUSR=CW=532&CH=667&DPR=2&UTC=480&WTS=63723633815&HV=1588039363
    sec-fetch-dest: document
    sec-fetch-mode: navigate
    sec-fetch-site: none
    sec-fetch-user: ?1
    upgrade-insecure-requests: 1
    user-agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.163 Safari/537.36
    """
    url = "https://cn.bing.com/search?q={}".format(output.replace(" ", "%20"))
    headers = get_headers(raw_headers)
    r = requests.get(url)
    print(r.status_code)
    # print(r.text)

if __name__ == '__main__':
    paths = [
        os.path.join(current_root, 'Leetcode'), 
        os.path.join(current_root, "Nowcoder")
    ] 

    outputs = []
    for path in paths:

        cmd = 'ls -t {path}'.format(path=path)
        
        description = execute_cmd(cmd)
        url = 'Leetcode/' + description.replace(' ', '%20')
        output = '|  |   | [{description}]({url}) |       |      | '.format(description = description, url = url)
        outputs.append(output)

    if sys.platform == 'dawin':
        copy_cmd = "pbcopy"
        cmd = "echo '%s' | %s" % '\n'.join(outputs, copy_cmd)
    else:
        cmd = "echo '%s'" % '\n'.join(outputs)
    print(execute_cmd(cmd))
