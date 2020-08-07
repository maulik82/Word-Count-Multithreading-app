#include "input_stream.h"



/**
* Calculates word count for the input stream
*/
void InputStream::calculateWordCount() {

    std::unique_lock<std::mutex> locker(mu_);
    std::string tmp = contents2_; //TODO: do we need to clear contents?
    contents2_.clear();
    locker.unlock();
    std::string word = "";
    for (auto x : tmp)
    {
        if (x == ' ')
        {
            if(!word.empty()){
                std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::tolower(c); });  // convert all to lowercase
                words.push_back( word );
                word = "";
            }
        }
        else if(isalpha(x))   // TODO: check if any special chars such as '-' needs to be considered as part of word
            word = word + x;
    }
    if(!word.empty()){
        // push last word
        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::tolower(c); }); // convert all to lowercase
        words.push_back( word );
    }

     //    DEBUG
//     std::cout << "Number of words: " << words.size() << "\n";
//     for (auto ele: words)
//         std::cout << ele <<",";
//     std::cout << std::endl;
    
    wordCountMap = countWords( words );  // update word count map
    
    std::unique_lock<std::mutex> locker2(mu_words_);
    words_accumulated.insert(words_accumulated.end(), words.begin(), words.end());
    locker2.unlock();
    words.clear();
 }

/**
* Prints already calculated word count for the input stream
*/
void InputStream::printWordCount()
{
      std::vector<std::pair<size_t, std::string>> output_map  = invertMap2(wordCountMap);

    // sort the vector pair to get  results similar to a map
      sort(output_map.begin(),  output_map.end(),    [](std::pair<size_t, std::string>& a,    std::pair<size_t, std::string>& b)
      {
          if (a.first != b.first)
              return a.first > b.first;
          return a.second > b.second;
      });
    
      for (auto it  = output_map.begin();  it != output_map.end();  ++it)
          std::cout << it->second << " : "  << it->first << ", ";
}

/**
 * Create an InputStream that reads from a string
 * @param contents The characters to return
 * @param seed A seed for the random delays (only used if 'slow' is true)
 * @param slow Simulate a slow source by delaying TakeChar() calls
 */
InputStream::InputStream(std::string contents, int seed, bool slow)
    : contents_{std::move(contents)}, slow_{slow} {
  rng_.seed(seed);
}



/**
*   Default constructor
*/
InputStream::InputStream()
    : InputStream{kExampleText, 500, false} {}

void InputStream::readStream() {
    char ch;
    while( TakeChar(ch) ){
        std::unique_lock<std::mutex> locker(mu_);
        contents2_+=ch;
        locker.unlock();
    }
    std::cout << "Read complete.. " << std::endl;
}



/**
 * Read a character from the stream. Returns false on EOF (and doesn't update
 * 'ch')
 * @param ch The character that was read
 * @return True if a character was returned
 */

bool InputStream::TakeChar(char &ch) {
    if (slow_) {
        int sleep_time = dist_(rng_);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }

    if (index_ >= contents_.size()) {
        return false;
    }

    ch = contents_[index_++];
        return true;
}






const char *kExampleText = R"(
    Alice was beginning to get very tired of sitting by her sister on the
    bank, and of having nothing to do: once or twice she had peeped into
    the book her sister was reading, but it had no pictures or
    conversations in it, “and what is the use of a book,” thought Alice
    “without pictures or conversations?”

    So she was considering in her own mind (as well as she could, for the
    hot day made her feel very sleepy and stupid), whether the pleasure of
    making a daisy-chain would be worth the trouble of getting up and
    picking the daisies, when suddenly a White Rabbit with pink eyes ran
    close by her.

    There was nothing so _very_ remarkable in that; nor did Alice think it
    so _very_ much out of the way to hear the Rabbit say to itself, “Oh
    dear! Oh dear! I shall be late!” (when she thought it over afterwards,
    it occurred to her that she ought to have wondered at this, but at the
    time it all seemed quite natural); but when the Rabbit actually _took a
    watch out of its waistcoat-pocket_, and looked at it, and then hurried
    on, Alice started to her feet, for it flashed across her mind that she
    had never before seen a rabbit with either a waistcoat-pocket, or a
    watch to take out of it, and burning with curiosity, she ran across the
    field after it, and fortunately was just in time to see it pop down a
    large rabbit-hole under the hedge.

    In another moment down went Alice after it, never once considering how
    in the world she was to get out again.

    The rabbit-hole went straight on like a tunnel for some way, and then
    dipped suddenly down, so suddenly that Alice had not a moment to think
    about stopping herself before she found herself falling down a very
    deep well)";
