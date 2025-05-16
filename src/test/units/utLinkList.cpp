#include "LinkList.h"
#include <cstddef>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace doengine
{
namespace ut
{

class utLinkedList : public ::testing::Test
{
  public:
    void SetUp() override
    {
        ::testing::Test::SetUp();

        _list.insert(0xAFFAB1E);
        _list.insert(0xABBA);
        _list.insert(0xDEADBEEF);
    }

    LinkList<int> _list;
};

TEST(LinkListTests, InsertTest)
{
    const int nodeData = 0xCAFEBABE;
    LinkList<int> list;

    list.insert(nodeData);

    EXPECT_EQ(list.getHead()->data, nodeData);
}

TEST_F(utLinkedList, TraverseTest)
{
    const int nodeData = 0xCAFEBABE;
    LinkList<int>::Node* tempNode = nullptr;

    tempNode = _list.getHead();

    EXPECT_EQ(tempNode->data, 0xAFFAB1E);
    tempNode = tempNode->next();
    EXPECT_EQ(tempNode->data, 0xABBA);
    tempNode = tempNode->next();
    EXPECT_EQ(tempNode->data, 0xDEADBEEF);
    tempNode = tempNode->next();
    EXPECT_EQ(_list.getLength(), 3);
}

TEST_F(utLinkedList, RemoveTest)
{
    using Node = LinkList<int>::Node;
    const int nodeData = 0xDEADBEEF;

    EXPECT_EQ(_list.getLength(), 3);

    auto deletedValue = _list.remove(nodeData);

    EXPECT_EQ(deletedValue, nodeData);
    EXPECT_EQ(_list.getLength(), 2);

    deletedValue = _list.remove(0xBABA);

    EXPECT_EQ(deletedValue, 0);
    EXPECT_EQ(_list.getLength(), 2);
}

TEST_F(utLinkedList, DestroyTest)
{

    EXPECT_EQ(_list.getLength(), 3);

    _list.destroy();

    EXPECT_EQ(_list.getHead(), nullptr);
    EXPECT_EQ(_list.getLength(), 0);
}

TEST_F(utLinkedList, InsertBeforeTest)
{

    auto tempNode = _list.getHead()->next(); // The Dancing Queeeeen!

    /* CURRENT LL
      HEAD - AFFABLE
      NEXT - ABBA
      NEXT - DEAD BEEF
    */

    _list.insertBefore(tempNode, 0xDEADBEEF);

    /* CURRENT LL
      HEAD - AFFABLE
      NEXT - DEAD BEEF
      NEXT - ABBA
      NEXT - DEAD BEEF
    */

    EXPECT_EQ(_list.getHead()->next()->data, 0xDEADBEEF);
    tempNode = _list.getHead()->next();
    EXPECT_EQ(tempNode->next()->data, 0xABBA);
    EXPECT_EQ(_list.getLength(), 4);

    tempNode = _list.getHead();

    _list.insertBefore(tempNode, 0xCAFEBABE);

    /* CURRENT LL
      HEAD - CAFE BABE
      NEXT - AFFABLE
      NEXT - DEAD BEEF
      NEXT - THE DANCING QUEEEN
      NEXT - DEAD BEEF
    */
 
    EXPECT_EQ(tempNode->data, 0xAFFAB1E);
    EXPECT_EQ(_list.getHead()->data, 0xCAFEBABE);
    EXPECT_EQ(_list.getLength(), 5);

}

TEST_F(utLinkedList, InsertAfterTest)
{
    auto tempNode = _list.getHead()->next();

    /* CURRENT LL
      HEAD - AFFABLE
      NEXT - ABBA
      NEXT - DEAD BEEF
    */

    _list.insertAfter(tempNode, 0xCAFEBABE);

    /* CURRENT LL
      HEAD - AFFABLE
      NEXT - ABBA
      NEXT - CAFE BABE
      NEXT - DEAD BEEF
    */

    EXPECT_EQ(tempNode->data, 0xABBA);
    tempNode = tempNode->next();
    EXPECT_EQ(tempNode->data, 0xCAFEBABE);
    EXPECT_EQ(_list.getLength(), 4);
    
    tempNode = _list.getHead();
    _list.insertBefore(tempNode, 0xBEBACAFE);
    
    /* CURRENT LL
      HEAD - AFFABLE
      NEXT - ABBA
      NEXT - BEBA CAFE
      NEXT - DEAD BEEF
    */

    EXPECT_EQ(tempNode->data, 0xAFFAB1E);
    tempNode = tempNode->next();
    EXPECT_EQ(tempNode->data, 0xABBA);
    EXPECT_EQ(_list.getLength(), 5);
}

TEST_F(utLinkedList, FindTest)
{
    auto tempNode = _list.find(0xDEADBEEF);

    EXPECT_NE(tempNode, nullptr);
    EXPECT_EQ(tempNode->data, 0xDEADBEEF);

    tempNode = _list.find(0xBABA);

    EXPECT_EQ(tempNode, nullptr);
}

} // namespace ut
} // namespace doengine
