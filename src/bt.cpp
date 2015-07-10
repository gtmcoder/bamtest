#include </Users/marth/Dropbox/Unix/Software/bamtest/bamtools/include/api/BamMultiReader.h>
#include </Users/marth/Dropbox/Unix/Software/bamtest/bamtools/include/api/BamWriter.h>
using namespace BamTools;


// standard includes
#include <iostream>
#include <string>
#include <vector>

int main (int argc, char *argv[]) {

  std::cout << "Hello!" << std::endl;

  // file names
  std::vector<std::string> inputFilenames;
  inputFilenames.push_back("mutated_genome.bam");
  std::string outputFilename = "out.bam";
  
  //std::cout << "inputFilename=" << inputFilename << " outputFilename=" << outputFilename << std::endl;

  // attempt to open our BamMultiReader
  BamMultiReader reader;
  if ( !reader.Open(inputFilenames) ) {
    std::cerr << "Could not open input BAM files." << std::endl;
    return 1;
  }
  
  // retrieve 'metadata' from BAM files, these are required by BamWriter
  const SamHeader header = reader.GetHeader();
  const RefVector references = reader.GetReferenceData();
  
  // attempt to open our BamWriter
  BamWriter writer;
  if ( !writer.Open(outputFilename, header, references) ) {
    std::cerr << "Could not open output BAM file" << std::endl;
    return (1);
  }
  // iterate through all alignments, only keeping ones with high map quality
  BamAlignment al;
  long int count1 = 0;
  long int count2 = 0;
  while ( reader.GetNextAlignmentCore(al) ) {
    count1++;
    if ( al.MapQuality >= 30 ) {
      writer.SaveAlignment(al);
      count2++;
    }
    std::cout << "count1=" << count1 << " count2=" << count2 << std::endl;
  }
  
  // close the reader & writer
  reader.Close();
  writer.Close();		   
}
