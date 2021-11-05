#include <gtest/gtest.h>
#include "../include/word.hpp"


TEST(ExactMatchTest, ExactMatchNotEqual) {
    Word w1("a");
    Word w2("b");
    ASSERT_EQ(false, w1.exactMatch(w2));
    w1.set("aaabb");
    w2.set("ubbcc");
    ASSERT_EQ(false, w1.exactMatch(w2));
    w1.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w2.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    ASSERT_EQ(false, w1.exactMatch(w2));
    w2.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w1.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    ASSERT_EQ(false, w1.exactMatch(w2));
}

TEST(ExactMatchTest, ExactMatchEqual) {
    Word w1("a");
    Word w2("a");
    ASSERT_EQ(true, w1.exactMatch(w2));
    w1.set("aaabb");
    w2.set("aaabb");
    ASSERT_EQ(true, w1.exactMatch(w2));
    w1.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    ASSERT_EQ(true, w1.exactMatch(w2));
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    w1.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    ASSERT_EQ(true, w1.exactMatch(w2));
}


TEST(ExactMatchTest, ExactMatchEmpty) {
    Word w1("a");
    Word w2("");
    ASSERT_EQ(false, w1.exactMatch(w2));
    w1.set("");
    w2.set("aaabb");
    ASSERT_EQ(false, w1.exactMatch(w2));
    w1.set("");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    ASSERT_EQ(false, w1.exactMatch(w2));
}

TEST(hammingDistanceTest, HammingDistEqual) {
    Word w1("a");
    Word w2("b");
    ASSERT_EQ(1, w1.hammingDist(w2));
    w1.set("aaabb");
    w2.set("ubbcc");
    ASSERT_EQ(5, w1.hammingDist(w2));
    w1.set("kjhgfyuiokbgft&*GTijhbvft67ihGt7ijhgFT^&*IUYFGHJki76ytFCVJI&^TFVBJ");
    w2.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67ui");
    ASSERT_EQ(66, w1.hammingDist(w2));
}

TEST(hammingDistanceTest, HammingDistNotEqual) {
    Word w1("a");
    Word w2("a");
    ASSERT_EQ(0, w1.hammingDist(w2));
    w1.set("aaabb");
    w2.set("aaabb");
    ASSERT_EQ(0, w1.hammingDist(w2));
    w1.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    ASSERT_EQ(0, w1.hammingDist(w2));
}

TEST(hammingDistanceTest, HammingDistDiffLength) {
    Word w1("a");
    Word w2("");
    ASSERT_EQ(-1, w1.hammingDist(w2));
    w1.set("");
    w2.set("aaabb");
    ASSERT_EQ(-1, w1.hammingDist(w2));
    w1.set("");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    ASSERT_EQ(-1, w1.hammingDist(w2));
    w1.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w2.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    ASSERT_EQ(-1, w1.hammingDist(w2));
    w2.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w1.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    ASSERT_EQ(-1, w1.hammingDist(w2));
}

TEST(EditDistanceTest, EditDistanceNotEqual) {
    Word w1("a");
    Word w2("b");
    ASSERT_EQ(1, w1.editDist(w2));
    w1.set("aaabb");
    w2.set("ubbcc");
    ASSERT_EQ(5, w1.editDist(w2));
    w1.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w2.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    ASSERT_EQ(57, w1.editDist(w2));
    w2.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w1.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    ASSERT_EQ(57, w1.editDist(w2));
    w1.set("kjhgfyuiokbgft&*GTijhbvft67ihGt7ijhgFT^&*IUYFGHJki76ytFCVJI&^TFVBJ");
    w2.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67ui");
    ASSERT_EQ(63, w1.editDist(w2));
}

TEST(EditDistanceTest, EditDistanceEqual) {
    Word w1("a");
    Word w2("a");
    ASSERT_EQ(0, w1.editDist(w2));
    w1.set("aaabb");
    w2.set("aaabb");
    ASSERT_EQ(0, w1.editDist(w2));
    w1.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    ASSERT_EQ(0, w1.editDist(w2));
}


TEST(EditDistanceTest, EditDistanceEmpty) {
    Word w1("a");
    Word w2("");
    ASSERT_EQ(1, w1.editDist(w2));
    w1.set("");
    w2.set("aaabb");
    ASSERT_EQ(5, w1.editDist(w2));
    w1.set("");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    ASSERT_EQ(55, w1.editDist(w2));
}
