#Colour codes
RED='\033[0;31m'
NC='\033[0m' # No Colour
PUR='\033[0;35m'

echo ""
echo -e "Compiling '${RED}DrawMandelbrot.C${NC}' as '${PUR}DM${NC}'..."
gcc DrawMandelbrot.C -o DM

echo ""
echo -e "Running '${RED}DrawMandelbrot.C${NC}'..."
./DM

echo -e "Using gnuplot to make graphs..."
gnuplot GRAPH.p

echo -e "${RED}Finished${NC}!"
echo ""

