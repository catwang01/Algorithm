import os


os.chdir("Leetcode")
for file in os.listdir():
    if file.startswith("Leetcode-"):
        newfilename = file.replace("Leetcode-", "Leetcode ")
        os.rename(file, newfilename)
