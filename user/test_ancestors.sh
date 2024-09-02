echo "Testing ancestors"
echo "----------------"
echo "Shell PID: $(yosoytupadre 0)"
echo "Parent (init) PID: $(yosoytupadre 1)"
echo "Grandparent PID: $(yosoytupadre 2)"
echo ""
echo "Forking a child process:"
sh -c '
  echo "  Child shell PID: $(yosoytupadre 0)"
  echo "  Parent (original shell) PID: $(yosoytupadre 1)"
  echo "  Grandparent (init) PID: $(yosoytupadre 2)"
  echo "  Great-grandparent PID: $(yosoytupadre 3)"
'
echo ""
echo "Testing invalid ancestor:"
yosoytupadre 10