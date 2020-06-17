/**
 * PrimePlot.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * An implementation of primes plotted as polar coordinates.
 */

#include "PrimePlot.h"

bool PrimePlot::isPrime(int val) {

    for (int i = 2; i*i <= val; i++) {
        if (val % i == 0) {
            return false;
        }
    }

    return true;
}

/*
 * Output SVG header.
 */
void PrimePlot::headerSVG(std::ofstream& outfile, int width, int height, std::string file) {

    std::string svgHeaderPart1="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
                               "<!-- Created with CurveBenchmark -->\n"
                               "<svg\n"
                               "    xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
                               "    xmlns:cc=\"http://creativecommons.org/ns#\"\n"
                               "    xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                               "    xmlns:svg=\"http://www.w3.org/2000/svg\"\n"
                               "    xmlns=\"http://www.w3.org/2000/svg\"\n"
                               "    xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n"
                               "    xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
                               "    xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n"
                               "    width=\"";
    std::string svgHeaderPart2="\"\n"
                               "    height=\"";
    std::string svgHeaderPart3="\"\n"
                               "    id=\"svg2\"\n"
                               "    version=\"1.1\"\n"
                               //		"    inkscape:version=\"0.48.1 r9760\"\n"
                               "    sodipodi:docname=\"";
    std::string svgHeaderPart4 = "\">\n"
                                 "<defs\n"
                                 "    id=\"defs4\" />\n"
                                 "<metadata\n"
                                 "    id=\"metadata7\">\n"
                                 "    <rdf:RDF>\n"
                                 "        <cc:Work\n"
                                 "            rdf:about=\"\">\n"
                                 "            <dc:format>image/svg+xml</dc:format>\n"
                                 "            <dc:type\n"
                                 "                rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\" />\n"
                                 "            <dc:title></dc:title>\n"
                                 "        </cc:Work>\n"
                                 "    </rdf:RDF>\n"
                                 "</metadata>\n"
                                 "<g\n"
                                 "    inkscape:label=\"Layer 1\"\n"
                                 "    inkscape:groupmode=\"layer\"\n"
                                 "    id=\"layer1\">\n";

    outfile << svgHeaderPart1 << width << svgHeaderPart2 << height << svgHeaderPart3 << file << svgHeaderPart4 << std::endl;
}

/*
 * Output SVG footer.
 */
void PrimePlot::footerSVG(std::ofstream& outfile) {
    std::string svgFooter = "    </g>\n"
                            "</svg>";

    outfile << svgFooter << std::endl;
}

/*
 * Generates prime plot as SVG.
 */
void PrimePlot::generatePrimePlot() {

    std::string file = "Prime Distribution";
    std::string filename = "../Analysis/Distribution/primeDistribution.bmp";
    printf("\nAttempting to write prime distribution as SVG.\n");

    filename = "../Analysis/Distribution/primeDistribution.svg";
    std::ofstream outfile;
    outfile.open(filename);

    int initialWidth = 1000, initialHeight = 1000;
    int marginX = 200, marginY = 200;
    int scaleFactor = 4.0f;
    int outputWidth = (initialWidth + marginX) / scaleFactor, outputHeight = (initialHeight + marginY) / scaleFactor;
    float radius = 0.25f;

    headerSVG(outfile, outputWidth, outputHeight, file);

    int limit = 50000;
    float limitFactor = 0.002f;

    for (int i = 0; i < limit; i++) {

        if (isPrime(i)) {
            float currX = ((marginX / 2) + (limit + i * cos(i)) / (float)(limit * limitFactor)) / scaleFactor;
            float currY = ((marginY / 2) + (limit - i * sin(i)) / (float)(limit * limitFactor)) / scaleFactor;

            float factor = (float)i / (float)limit;

            // Blue gradient
            /*int r = 0 + 134 * factor;
            int g = 83 + 136 * factor;
            int b = 95 + 137 * factor;*/

            // Green-blue gradient
            /*int r = 67 - 42 * factor;
            int g = 198 - 170 * factor;
            int b = 172 - 88 * factor;*/

            // Black
            int r = 0;
            int g = 0;
            int b = 0;

            // Create RGB string
            std::string rgb = "rgb(";
            rgb += std::to_string(r);
            rgb += ",";
            rgb += std::to_string(g);
            rgb += ",";
            rgb += std::to_string(b);
            rgb += ")";

            outfile << "    <circle cx=\"" << currX << "\" cy=\"" << currY << "\" r=\"" << radius << "\" fill=\"" << rgb << "\" stroke=\"" << rgb << "\" id=\"circle" << i << "\"/>\n";
        }
    }

    // Draw Cartesian gridlines
    /*outfile << "    <line x1=\"100\" y1=\"600\" x2=\"1100\" y2=\"600\" stroke=\"black\" />";        // X Axis
    outfile << "    <line x1=\"600\" y1=\"100\" x2=\"600\" y2=\"1100\" stroke=\"black\" />";        // Y Axis
    outfile << "    <line x1=\"100\" y1=\"100\" x2=\"100\" y2=\"1100\" stroke=\"black\" />";        // Left
    outfile << "    <line x1=\"1100\" y1=\"100\" x2=\"1100\" y2=\"1100\" stroke=\"black\" />";      // Right
    outfile << "    <line x1=\"100\" y1=\"1100\" x2=\"1100\" y2=\"1100\" stroke=\"black\" />";      // Bottom
    outfile << "    <line x1=\"100\" y1=\"100\" x2=\"1100\" y2=\"100\" stroke=\"black\" />";        // Top*/
    outfile << "    <line x1=\"25\" y1=\"150\" x2=\"275\" y2=\"150\" stroke=\"black\" />";        // X Axis
    outfile << "    <line x1=\"150\" y1=\"25\" x2=\"150\" y2=\"275\" stroke=\"black\" />";        // Y Axis
    outfile << "    <line x1=\"25\" y1=\"25\" x2=\"25\" y2=\"275\" stroke=\"black\" />";        // Left
    outfile << "    <line x1=\"275\" y1=\"25\" x2=\"275\" y2=\"275\" stroke=\"black\" />";      // Right
    outfile << "    <line x1=\"25\" y1=\"275\" x2=\"275\" y2=\"275\" stroke=\"black\" />";      // Bottom
    outfile << "    <line x1=\"25\" y1=\"25\" x2=\"275\" y2=\"25\" stroke=\"black\" />";        // Top

    // Draw tickmarks
    //outfile << "    <line x1=\"350\" y1=\"100\" x2=\"350\" y2=\"1100\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Left
    //outfile << "    <line x1=\"850\" y1=\"100\" x2=\"850\" y2=\"1100\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Right
    //outfile << "    <line x1=\"100\" y1=\"350\" x2=\"1100\" y2=\"350\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Bottom
    //outfile << "    <line x1=\"100\" y1=\"850\" x2=\"1100\" y2=\"850\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Top

    // Draw polar gridlines
    /*outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 500 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 375 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 250 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 125 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";*/
    outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 500 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 375 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 250 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 125 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";

    // Polar axis labels
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"12.5\" y=\"150\" font-size=\"10px\">180&#xb0;</text>";              // Left
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"287.5\" y=\"150\" font-size=\"10px\">0&#xb0;</text>";             // Right
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"150\"  y=\"12.5\" font-size=\"10px\">90&#xb0;</text>";              // Top
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"150\" y=\"287.5\" font-size=\"10px\">270&#xb0;</text>";            // Bottom

    // Polar axis radius labels
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"181.25\" y=\"181.25\" font-size=\"10px\">2500</text>";            // tick right 1
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"212.5\" y=\"212.5\" font-size=\"10px\">5000</text>";            // tick right 2
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"243.75\" y=\"243.75\" font-size=\"10px\">7500</text>";            // tick right 3

    footerSVG(outfile);
    outfile.close();

    filename = "../Analysis/Distribution/primeDistribution.SVG";
    printf("    SVG written: %s\n", filename.c_str());
    printf("Successfully wrote prime distribution as SVG.\n");
}

/*
 * Generate primes along unit circle as SVG.
 */
void PrimePlot::generateUnitCircle() {

    std::string file = "Prime Unit Circle Distribution";
    printf("\nAttempting to write prime unit circle distribution as SVG.\n");

    std::string filename = "../Analysis/Distribution/primeUnitCircle.svg";
    std::ofstream outfile;
    outfile.open(filename);

    int initialWidth = 1000, initialHeight = 1000;
    int marginX = 0, marginY = 0;
    int scaleFactor = 1.0f;
    int outputWidth = (initialWidth + marginX) / scaleFactor, outputHeight = (initialHeight + marginY) / scaleFactor;
    float radius = 2.0f;

    headerSVG(outfile, outputWidth, outputHeight, file);

    int current = 2;
    int count = 0;
    int numPrimes = 256;
    int primes[numPrimes];

    int countOffset = 0;
    //int offset = 0;
    int offset = pow(2, 16);

    // Loop until numPrimes is reached
    while (count < numPrimes) {
        if (isPrime(current) || current == 2 || current == 3) {
            if (++countOffset > offset) {
                primes[count++] = current;
            }
        }

        current++;
    }

    int min = primes[0];
    int max = primes[numPrimes - 1];
    for (int i = 0; i < numPrimes; i++) {
        float currX = ((500 + cos(primes[i]) * 475));
        float currY = ((500 - sin(primes[i]) * 475));

        float factor = (primes[i] - min) / (float)(max - min);

        // Blue gradient
        /*int r = 0 + 134 * factor;
        int g = 83 + 136 * factor;
        int b = 95 + 137 * factor;*/

        // Green-blue gradient
        int r = 67 - 42 * factor;
        int g = 198 - 170 * factor;
        int b = 172 - 88 * factor;

        // Black
        /*int r = 0;
        int g = 0;
        int b = 0;*/

        // Create RGB string
        std::string rgb = "rgb(";
        rgb += std::to_string(r);
        rgb += ",";
        rgb += std::to_string(g);
        rgb += ",";
        rgb += std::to_string(b);
        rgb += ")";

        outfile << "    <circle cx=\"" << currX << "\" cy=\"" << currY << "\" r=\"" << radius << "\" fill=\"" << rgb << "\" stroke=\"" << rgb << "\" id=\"circle" << count++ << "\"/>\n";
    }

    // Draw Cartesian gridlines
    /*outfile << "    <line x1=\"100\" y1=\"600\" x2=\"1100\" y2=\"600\" stroke=\"black\" />";        // X Axis
    outfile << "    <line x1=\"600\" y1=\"100\" x2=\"600\" y2=\"1100\" stroke=\"black\" />";        // Y Axis
    outfile << "    <line x1=\"100\" y1=\"100\" x2=\"100\" y2=\"1100\" stroke=\"black\" />";        // Left
    outfile << "    <line x1=\"1100\" y1=\"100\" x2=\"1100\" y2=\"1100\" stroke=\"black\" />";      // Right
    outfile << "    <line x1=\"100\" y1=\"1100\" x2=\"1100\" y2=\"1100\" stroke=\"black\" />";      // Bottom
    outfile << "    <line x1=\"100\" y1=\"100\" x2=\"1100\" y2=\"100\" stroke=\"black\" />";        // Top*/
    outfile << "    <line x1=\"1\" y1=\"500\" x2=\"999\" y2=\"500\" stroke=\"black\" opacity=\"0.2\" />";        // X Axis
    outfile << "    <line x1=\"500\" y1=\"1\" x2=\"500\" y2=\"999\" stroke=\"black\" opacity=\"0.2\" />";        // Y Axis
    outfile << "    <line x1=\"1\" y1=\"1\" x2=\"1\" y2=\"999\" stroke=\"black\" opacity=\"0.2\" />";        // Left
    outfile << "    <line x1=\"999\" y1=\"1\" x2=\"999\" y2=\"999\" stroke=\"black\" opacity=\"0.2\" />";      // Right
    outfile << "    <line x1=\"1\" y1=\"999\" x2=\"999\" y2=\"999\" stroke=\"black\" opacity=\"0.2\" />";      // Bottom
    outfile << "    <line x1=\"1\" y1=\"1\" x2=\"999\" y2=\"1\" stroke=\"black\" opacity=\"0.2\"/>";        // Top

    // Draw tickmarks
    //outfile << "    <line x1=\"350\" y1=\"100\" x2=\"350\" y2=\"1100\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Left
    //outfile << "    <line x1=\"850\" y1=\"100\" x2=\"850\" y2=\"1100\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Right
    //outfile << "    <line x1=\"100\" y1=\"350\" x2=\"1100\" y2=\"350\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Bottom
    //outfile << "    <line x1=\"100\" y1=\"850\" x2=\"1100\" y2=\"850\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Top

    // Draw polar gridlines
    /*outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 500 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 375 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 250 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 125 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";*/
    outfile << "    <circle cx=\"" << 500 << "\" cy=\"" << 500 << "\" r=\"" << 475 - 0.25f  << "\" stroke=\"black\" opacity=\"0.2\" fill=\"none\" id=\"circle100001\" />\n";
    //outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 375 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    //outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 250 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    //outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 125 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";

    // Polar axis labels
    /*outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"12.5\" y=\"150\" font-size=\"10px\" opacity=\"0.4\">180&#xb0;</text>";              // Left
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"287.5\" y=\"150\" font-size=\"10px\" opacity=\"0.4\">0&#xb0;</text>";             // Right
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"150\"  y=\"12.5\" font-size=\"10px\" opacity=\"0.4\">90&#xb0;</text>";              // Top
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"150\" y=\"287.5\" font-size=\"10px\" opacity=\"0.4\">270&#xb0;</text>";            // Bottom*/

    // Polar axis radius labels
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"181.25\" y=\"181.25\" font-size=\"10px\">2500</text>";            // tick right 1
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"212.5\" y=\"212.5\" font-size=\"10px\">5000</text>";            // tick right 2
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"243.75\" y=\"243.75\" font-size=\"10px\">7500</text>";            // tick right 3

    footerSVG(outfile);
    outfile.close();

    filename = "../Analysis/Distribution/primeUnitCircle.SVG";
    printf("    SVG written: %s\n", filename.c_str());
    printf("Successfully wrote prime unit circle distribution as SVG.\n");
}

/*
 * Generates gradient figure for report.
 */
void PrimePlot::generateGradientSVG() {
    std::string file = "Gradient Figure";
    printf("\nAttempting to write gradient figure as SVG.\n");

    std::string filename = "../Analysis/Distribution/gradientFigure.svg";
    std::ofstream outfile;
    outfile.open(filename);

    int initialWidth = 1000, initialHeight = 1000;

    headerSVG(outfile, initialWidth, initialHeight, file);

    // Draw points
    int count = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    std::string rgb = "rgb(";
    rgb += std::to_string(r);
    rgb += ",";
    rgb += std::to_string(g);
    rgb += ",";
    rgb += std::to_string(b);
    rgb += ")";

    /// Arrowhead
    outfile << "<marker id=\"arrowheadBlack\" viewBox=\"0 0 60 60\" refX=\"30\" refY=\"30\" markerUnits=\"strokeWidth\" markerWidth=\"4\" markerHeight=\"4\" orient=\"auto\"> <path d=\"M 0 0 L 60 30 L 0 60 z\" fill=\"#000000\" /> </marker>\n";
    outfile << "<marker id=\"arrowheadLightBlue\" viewBox=\"0 0 60 60\" refX=\"30\" refY=\"30\" markerUnits=\"strokeWidth\" markerWidth=\"4\" markerHeight=\"4\" orient=\"auto\"> <path d=\"M 0 0 L 60 30 L 0 60 z\" fill=\"#43c6ac\" /> </marker>\n";
    outfile << "<marker id=\"arrowheadDarkBlue\" viewBox=\"0 0 60 60\" refX=\"30\" refY=\"30\" markerUnits=\"strokeWidth\" markerWidth=\"4\" markerHeight=\"4\" orient=\"auto\"> <path d=\"M 0 0 L 60 30 L 0 60 z\" fill=\"#2e7180\" /> </marker>\n";

    /// Vectors (gradient)
    r = 46;         // dark blue
    g = 113;
    b = 128;
    rgb = "rgb(";
    rgb += std::to_string(r);
    rgb += ",";
    rgb += std::to_string(g);
    rgb += ",";
    rgb += std::to_string(b);
    rgb += ")";

    outfile << "    <line marker-end=\"url(#arrowheadDarkBlue)\" x1=\"333\" y1=\"333\" x2=\"642.451127\" y2=\"210\" stroke=\"" << rgb << "\"  stroke-width=\"3\" opacity=\"1.0\" />";        // Top left
    outfile << "    <line marker-end=\"url(#arrowheadDarkBlue)\" x1=\"333\" y1=\"666\" x2=\"480\" y2=\"362\" stroke=\"" << rgb << "\"  stroke-width=\"3\" opacity=\"1.0\" />";     // Bottom left
    outfile << "    <line marker-end=\"url(#arrowheadDarkBlue)\" x1=\"666\" y1=\"333\" x2=\"600\" y2=\"659.3939338\" stroke=\"" << rgb << "\"  stroke-width=\"3\" opacity=\"1.0\" />";     // Top right
    outfile << "    <line marker-end=\"url(#arrowheadDarkBlue)\" x1=\"666\" y1=\"666\" x2=\"866.3322241\" y2=\"400\" stroke=\"" << rgb << "\"  stroke-width=\"3\" opacity=\"1.0\" />";     // Bottom right

    // Labels of gradient vector
    outfile << "<text font-family=\"Times, serif\" fill=\"black\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"667\" y=\"210\" font-size=\"10px\">"
               "    <tspan font-size=\"12\" font-style=\"italic\">H(c<tspan font-size=\"8\" baseline-shift=\"sub\">0, 0</tspan>)</tspan>"
               "</text>";

    outfile << "<text font-family=\"Times, serif\" fill=\"black\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"505\" y=\"362\" font-size=\"10px\">"
               "    <tspan font-size=\"12\" font-style=\"italic\">H(c<tspan font-size=\"8\" baseline-shift=\"sub\">0, 1</tspan>)</tspan>"
               "</text>";

    outfile << "<text font-family=\"Times, serif\" fill=\"black\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"575\" y=\"659.3939338\" font-size=\"10px\">"
               "    <tspan font-size=\"12\" font-style=\"italic\">H(c<tspan font-size=\"8\" baseline-shift=\"sub\">1, 0</tspan>)</tspan>"
               "</text>";

    outfile << "<text font-family=\"Times, serif\" fill=\"black\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"891\" y=\"400\" font-size=\"10px\">"
               "    <tspan font-size=\"12\" font-style=\"italic\">H(c<tspan font-size=\"8\" baseline-shift=\"sub\">1, 1</tspan>)</tspan>"
               "</text>";

    /// Vectors (point)
    r = 67;         // light blue
    g = 198;
    b = 172;
    rgb = "rgb(";
    rgb += std::to_string(r);
    rgb += ",";
    rgb += std::to_string(g);
    rgb += ",";
    rgb += std::to_string(b);
    rgb += ")";

    outfile << "    <line marker-end=\"url(#arrowheadLightBlue)\" x1=\"333\" y1=\"333\" x2=\"445\" y2=\"522\" stroke=\"" << rgb << "\" stroke-width=\"3\" opacity=\"1.0\" />";         // Top left
    outfile << "    <line marker-end=\"url(#arrowheadLightBlue)\" x1=\"333\" y1=\"666\" x2=\"445\" y2=\"533\" stroke=\"" << rgb << "\" stroke-width=\"3\" opacity=\"1.0\" />";         // Bottom left
    outfile << "    <line marker-end=\"url(#arrowheadLightBlue)\" x1=\"666\" y1=\"333\" x2=\"455\" y2=\"523\" stroke=\"" << rgb << "\" stroke-width=\"3\" opacity=\"1.0\" />";         // Top right
    outfile << "    <line marker-end=\"url(#arrowheadLightBlue)\" x1=\"666\" y1=\"666\" x2=\"456\" y2=\"533\" stroke=\"" << rgb << "\" stroke-width=\"3\" opacity=\"1.0\" />";         // Bottom right

    /// Sample point
    r = 255;
    g = 0;
    b = 0;
    rgb = "rgb(";
    rgb += std::to_string(r);
    rgb += ",";
    rgb += std::to_string(g);
    rgb += ",";
    rgb += std::to_string(b);
    rgb += ")";
    outfile << "    <circle cx=\"" << 450 << "\" cy=\"" << 528 << "\" r=\"" << 2 << "\" fill=\"" << rgb << "\" stroke=\"" << rgb << "\" id=\"circle" << count++ << "\"/>\n";
    outfile << "<text font-family=\"Times, serif\" fill=\"black\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"475\" y=\"528\" font-size=\"10px\">"
               "    <tspan font-size=\"12\" font-style=\"italic\">p</tspan>"
               "</text>";

    /// Lattice
    r = 0;         // black
    g = 0;
    b = 0;
    rgb = "rgb(";
    rgb += std::to_string(r);
    rgb += ",";
    rgb += std::to_string(g);
    rgb += ",";
    rgb += std::to_string(b);
    rgb += ")";

    // Draw box
    outfile << "    <line x1=\"333\" y1=\"333\" x2=\"333\" y2=\"666\" stroke=\"black\" stroke-width=\"3\" opacity=\"1.0\"/>";         // Left
    outfile << "    <line x1=\"666\" y1=\"333\" x2=\"666\" y2=\"666\" stroke=\"black\" stroke-width=\"3\" opacity=\"1.0\"/>";         // Right
    outfile << "    <line x1=\"333\" y1=\"666\" x2=\"666\" y2=\"666\" stroke=\"black\" stroke-width=\"3\" opacity=\"1.0\"/>";         // Bottom
    outfile << "    <line x1=\"333\" y1=\"333\" x2=\"666\" y2=\"333\" stroke=\"black\" stroke-width=\"3\" opacity=\"1.0\"/>";          // Top

    // Draw points at corners of box
    outfile << "    <circle cx=\"" << 333 << "\" cy=\"" << 333 << "\" r=\"" << 2 << "\" fill=\"" << rgb << "\" stroke=\"" << rgb << "\" id=\"circle" << count++ << "\"/>\n";
    outfile << "    <circle cx=\"" << 333 << "\" cy=\"" << 666 << "\" r=\"" << 2 << "\" fill=\"" << rgb << "\" stroke=\"" << rgb << "\" id=\"circle" << count++ << "\"/>\n";
    outfile << "    <circle cx=\"" << 666 << "\" cy=\"" << 333 << "\" r=\"" << 2 << "\" fill=\"" << rgb << "\" stroke=\"" << rgb << "\" id=\"circle" << count++ << "\"/>\n";
    outfile << "    <circle cx=\"" << 666 << "\" cy=\"" << 666 << "\" r=\"" << 2 << "\" fill=\"" << rgb << "\" stroke=\"" << rgb << "\" id=\"circle" << count++ << "\"/>\n";

    // Labels at lattice points
    outfile << "<text font-family=\"Times, serif\" fill=\"black\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"310\" y=\"333\" font-size=\"10px\">"
               "    <tspan font-size=\"12\" font-style=\"italic\">c<tspan font-size=\"8\" baseline-shift=\"sub\">0, 0</tspan></tspan>"
               "</text>";

    outfile << "<text font-family=\"Times, serif\" fill=\"black\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"310\" y=\"666\" font-size=\"10px\">"
               "    <tspan font-size=\"12\" font-style=\"italic\">c<tspan font-size=\"8\" baseline-shift=\"sub\">0, 1</tspan></tspan>"
               "</text>";

    outfile << "<text font-family=\"Times, serif\" fill=\"black\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"690\" y=\"333\" font-size=\"10px\">"
               "    <tspan font-size=\"12\" font-style=\"italic\">c<tspan font-size=\"8\" baseline-shift=\"sub\">1, 0</tspan></tspan>"
               "</text>";

    outfile << "<text font-family=\"Times, serif\" fill=\"black\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"690\" y=\"666\" font-size=\"10px\">"
               "    <tspan font-size=\"12\" font-style=\"italic\">c<tspan font-size=\"8\" baseline-shift=\"sub\">1, 1</tspan></tspan>"
               "</text>";


    footerSVG(outfile);
    outfile.close();

    printf("    SVG written: %s\n", filename.c_str());
    printf("Successfully wrote gradient figure as SVG.\n");
}

float PrimePlot::fade(float x) {

    /**
     * In ascending order of slope at (0.5, 0.5). See image in analysis folder.
     * [1] and [2] very alike. [3] and [4] very alike.
     */

    // Cubic (original gradient noise) [1]
    //return x * x * (3.0f - 2.0f * x);

    // Cos ease [2]
    //return pow(cos(3.14159f * (x - 1.0f) / 2.0f), 2.0f);

    // Quintic (better gradient noise) [3]
    return ((6.0f * x - 15.0f) * x + 10.0f) * x * x * x;

    // Parametric [4]
    //return pow(x, 2.0f) / (pow(x, 2.0f) + pow(1.0f - x, 2.0f));

    // Higher order smoothing (via Kyle McDonald) [5]
    //return -20.0f * pow(x, 7) + 70.0f * pow(x, 6) - 84.0f * pow(x, 5) + 35.0f * pow(x, 4);

    // Averaged smoothing [6] (([3] + [5]) / 2)
    //return x * x * x * (-10.0f * x * x * x * x + 35.0f * x * x * x - 39.0f * x * x + 10.0f * x + 5.0f);
}