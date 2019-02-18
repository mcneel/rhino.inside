import os
from shutil import copyfile
os.system('python setup.py bdist_wheel')

generated_file = os.listdir("dist")[0]
parts = generated_file.split('-')

py27_wheel = parts[0] + "-" + parts[1] + "-cp27-cp27m-win_amd64.whl"
py36_wheel = parts[0] + "-" + parts[1] + "-cp36-cp36m-win_amd64.whl"
os.chdir("dist")
copyfile(generated_file, py27_wheel)
copyfile(generated_file, py36_wheel)
os.remove(generated_file)
