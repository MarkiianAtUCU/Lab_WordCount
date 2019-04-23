//
// Created by Vitaliy Vorobyov on 2019-04-23.
//

#include <string>
#include <map>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <fstream>

std::map<std::string, int> words_count(std::string text) {
    std::map<std::string, int> words_counter;

    char chars[] = ".,?!-';:\"`~@#$%^&*(()_+=[]{}/><|";

    std::transform(text.begin(), text.end(), text.begin(), ::tolower);


    for (int i = 0; i < strlen(chars); ++i) {
        text.erase(std::remove(text.begin(), text.end(), chars[i]), text.end());
    }

    std::string word;

    for(std::stringstream s(text); s >> word;) {
        std::map<std::string, int>::const_iterator itr = words_counter.find(word);

        if( itr!=words_counter.end() )
        {
            words_counter[word] += 1;
        }else{
            words_counter[word] = 1;
        }
    }

    return words_counter;
}

int main() {

    std::string str = "This edition of Milton's Poetry is a reprint, as careful as Editor\n"
                      "and Printers have been able to make it, from the earliest printed\n"
                      "copies of the several poems.  First the 1645 volume of the\n"
                      "Minor Poems has been printed entire; then follow in order the\n"
                      "poems added in the reissue of 1673; the Paradise Lost, from the\n"
                      "edition of 1667; and the Paradise Regain'd and Samson\n"
                      "Agonistes from the edition of 1671.\n"
                      "\n"
                      "The most interesting portion of the book must be reckoned the\n"
                      "first section of it, which reproduces for the first time the scarce\n"
                      "small octavo of 1645.  The only reprint of the Minor Poems in\n"
                      "the old spelling, so far as I know, is the one edited by Mitford,\n"
                      "but that followed the edition of 1673, which is comparatively\n"
                      "uninteresting since it could not have had Milton's oversight as it\n"
                      "passed through the press.  We know that it was set up from a\n"
                      "copy of the 1645 edition, because it reproduces some pointless\n"
                      "eccentricities such as the varying form of the chorus to Psalm\n"
                      "cxxxvi; but while it corrects the errata tabulated in that edition\n"
                      "it commits many more blunders of its own.  It is valuable,\n"
                      "however, as the editio princeps of ten of the sonnets and it\n"
                      "contains one important alteration in the Ode on the Nativity.\n"
                      "This and all other alterations will be found noted where they\n"
                      "occur.  I have not thought it necessary to note mere differences\n"
                      "of spelling between the two editions but a word may find place\n"
                      "here upon their general character.  Generally it may be said that,\n"
                      "where the two editions differ, the later spelling is that now in\n"
                      "use.  Thus words like goddess, darkness, usually written in the\n"
                      "first edition with one final s, have two, while on the  other hand\n"
                      "words like vernall, youthfull, and monosyllables like hugg, farr,\n"
                      "lose their double letter.  Many monosyllables, e.g. som, cours,\n"
                      "glimps, wher, vers, aw, els, don, ey, ly, so written in 1645, take\n"
                      "on in 1673 an e mute, while words like harpe, windes, onely,\n"
                      "lose it. By a reciprocal change ayr and cipress become air and\n"
                      "cypress; and the vowels in daign, vail, neer, beleeve, sheild,\n"
                      "boosom, eeven, battail, travailer, and many other words are\n"
                      "similarly modernized.  On the other hand there are a few cases\n"
                      "where the 1645 edition exhibits the spelling which has\n"
                      "succeeded in fixing itself, as travail (1673, travel) in the sense of\n"
                      "labour; and rob'd, profane, human, flood and bloody, forest,\n"
                      "triple, alas, huddling, are found where the 1673 edition has\n"
                      "roab'd, prophane, humane, floud and bloudy, forrest, tripple,\n"
                      "alass and hudling.  Indeed the spelling in this later edition is not\n"
                      "untouched by seventeenth century inconsistency.  It retains here\n"
                      "and there forms like shameles, cateres, (where 1645 reads\n"
                      "cateress), and occasionally reverts to the older-fashioned\n"
                      "spelling of monosyllables without the mute e.  In the Epitaph on\n"
                      "the Marchioness of Winchester, it reads --' And som flowers\n"
                      "and some bays.'  But undoubtedly the impression on the whole\n"
                      "is of a much more modern text.\n"
                      "\n"
                      "In the matter of small or capital letters I have followed the old\n"
                      "copy, except in one or two places where a personification\n"
                      "seemed not plainly enough marked to a modern reader without\n"
                      "a capital. Thus in Il Penseroso, l. 49, I print Leasure, although\n"
                      "both editions read leasure; and in the Vacation Exercise, l. 71,\n"
                      "Times for times. Also where the employment or omission of a\n"
                      "capital is plainly due to misprinting, as too frequently in the\n"
                      "1673 edition, I silently make the correction.  Examples are,\n"
                      "notes for Notes in Sonnet xvii. l. 13; Anointed for anointed in\n"
                      "Psalm  ii. l.12.\n"
                      "\n"
                      "In regard to punctuation I have followed the old printers except\n"
                      "in obvious misprints, and followed them also, as far as possible,\n"
                      "in their distribution of roman and italic type and in the grouping\n"
                      "of words and lines in the various titles. To follow them exactly\n"
                      "was impossible, as the  books are so very different in size.\n"
                      "\n"
                      "At this point the candid reader may perhaps ask what advantage\n"
                      "is gained by presenting these poems to modern readers in the\n"
                      "dress of a bygone age.  If the question were put to me I should\n"
                      "probably evade it by pointing out that Mr. Frowde is issuing an\n"
                      "edition based upon this, in which the spelling is frankly that of\n"
                      "to-day.  But if the question were pressed, I think a sufficient\n"
                      "answer might be found.  To begin with, I should point out that\n"
                      "even Prof. Masson, who in his excellent edition argues the\n"
                      "point and decides in favour of modern spelling, allows that there\n"
                      "are peculiarities of Milton's spelling which are really  significant,\n"
                      "and ought therefore to be noted or preserved.  But who is to\n"
                      "determine exactly which words are spelt according to the poet's\n"
                      "own instructions, and which according to the printer's whim?  It\n"
                      "is notorious that in Paradise Lost some words were spelt upon a\n"
                      "deliberate system, and it may very well happen that in the\n"
                      "volume of minor poems which the poet saw through the press in\n"
                      "1645, there were spellings no less systematic.  Prof. Masson\n"
                      "makes a great point of the fact that Milton's own spelling,\n"
                      "exhibited in the autograph manuscript of some of the minor\n"
                      "poems preserved in Trinity College, Cambridge, does not\n"
                      "correspond with that of the printed copy. [Note: This\n"
                      "manuscript, invaluable to all students of Milton, has lately been\n"
                      "facsimiled under the superintendence of Dr. Aldis Wright, and\n"
                      "published at the Cambridge University press].  This is certainly\n"
                      "true, as the reader may see for himself by comparing the\n"
                      "passage from the manuscript given in the appendix with the\n"
                      "corresponding place in the text.  Milton's own spelling revels in\n"
                      "redundant e's, while the printer of the 1645 book is very sparing\n"
                      "of them.  But in cases where the spelling affects the metre, we\n"
                      "find that the printed text and Milton's manuscript closely\n"
                      "correspond; and it is upon its value in determining the metre,\n"
                      "quite as much as its antiquarian interest, that I should base a\n"
                      "justification of this reprint.  Take, for instance, such a line as the\n"
                      "eleventh of Comus, which Prof. Masson gives as:-";

    std::map<std::string, int> test = words_count(str);

    for(auto it = test.cbegin(); it != test.cend(); ++it)
    {
        std::cout << it->first << " " << it->second << "\n";
    }

}
