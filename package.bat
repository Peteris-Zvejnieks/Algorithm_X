python setup.py sdist

python -m build --sdist

python setup.py bdist_wheel

pip wheel -w dist/ .

python -m build --wheel