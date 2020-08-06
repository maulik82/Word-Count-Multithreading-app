#ifndef WORDCOUNT__INPUT_STREAM_H_
#define WORDCOUNT__INPUT_STREAM_H_


#include "utils.h"



/**
 * A 'reader' style interface to a sequence of characters.
 */
class InputStream {
 public:
    /**
    * Create an InputStream that reads from a string
    * @param contents The characters to return
    * @param seed A seed for the random delays (only used if 'slow' is true)
    * @param slow Simulate a slow source by delaying TakeChar() calls
    */
    InputStream(std::string contents, int seed = 1, bool slow = false);

    /**
    * Read a character from the stream. Returns false on EOF (and doesn't update
    * 'ch')
    * @param ch The character that was read
    * @return True if a character was returned
    */
    bool TakeChar(char &ch);
    void PreProcess_Contents() ;
    void calculateAndPrintWordCount();
    void calculateWordCount();
    void printWordCount();
    void readStream();
    void readStream_slow();

    
    std::vector<std::string> words;     //TODO: REMOVE visibility once tested ok
    std::map<std::string, size_t> wordCountMap;

private:
    std::string contents_;
    std::string contents2_;
    std::stringstream contentsRead_;
    bool slow_;
    std::mt19937 rng_;
    std::uniform_int_distribution<int> dist_{1, 100};
    size_t index_{0};
    std::mutex mu_;
    
};

extern const char *kExampleText;

#endif  // WORDCOUNT__INPUT_STREAM_H_
