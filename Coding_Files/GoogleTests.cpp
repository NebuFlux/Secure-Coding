// Uncomment the next line to use precompiled headers
#include "pch.h"
// Uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// The global test environment setup and tear down.
// You should not need to change anything here.
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        // Initialize random seed.
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};


// Create our test fixture to house shared data between tests.
// You should not need to change anything here.
class CollectionTest : public ::testing::Test
{
protected:
    // Smart pointer that holds our collection.
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    {
        // Create a new collection to be used in each test.
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    {
        // Erase all elements in the collection, if any remain, then free pointer.
        collection->clear();
        collection.reset(nullptr);
    }

    // Helper function to add random values from 0 to 99 count times to the collection.
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called

TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}


// Test that a newly created collection is empty.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // Is the collection empty?
    ASSERT_TRUE(collection->empty());

    // If empty, the size must be 0.
    EXPECT_EQ(collection->size(), 0);
}


// Intentionally failing test to demonstrate a test failure in the test explorer.
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}


// Verify adding a single value to an empty collection.
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // Precondition: collection must be empty.
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    // Add one entry.
    add_entries(1);

    // Postconditions: collection should no longer be empty and size should be 1.
    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 1);
}


// Verify adding five values to the collection.
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // Precondition: collection must be empty.
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    // Add five entries.
    add_entries(5);

    // Postconditions: collection should no longer be empty and size should be 5.
    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 5);
}


// Verify that max_size() is greater than or equal to size() for sample sizes.
TEST_F(CollectionTest, MaxSizeIsGeVectorSize)
{
    // Sample collection sizes to test.
    const std::vector<int> entries{ 0, 1, 5, 10 };

    // Iterate through sample sizes.
    for (int entry : entries)
    {
        // Scope trace makes output clearer on failure.
        SCOPED_TRACE(entry);

        // Prepare collection for iteration.
        collection->clear();
        ASSERT_EQ(collection->size(), 0);

        // Add entries if requested.
        if (entry > 0)
        {
            add_entries(entry);
        }

        // Verify size and that max_size() is no less than size().
        ASSERT_EQ(collection->size(), static_cast<size_t>(entry));
        EXPECT_GE(collection->max_size(), collection->size());
    }
}


// Verify that capacity() is greater than or equal to size() for sample sizes.
TEST_F(CollectionTest, CapacityIsGeVectorSize)
{
    // Sample collection sizes to test.
    const std::vector<int> entries{ 0, 1, 5, 10 };

    // Iterate through sample sizes.
    for (int entry : entries)
    {
        // Scope trace makes output clearer on failure.
        SCOPED_TRACE(entry);

        // Prepare collection for iteration.
        collection->clear();
        ASSERT_EQ(collection->size(), 0);

        // Add entries if requested.
        if (entry > 0)
        {
            add_entries(entry);
        }

        // Verify size and that capacity() is no less than size().
        EXPECT_EQ(collection->size(), static_cast<size_t>(entry));
        EXPECT_GE(collection->capacity(), collection->size());
    }
}


// Verify that resizing to a larger size increases the collection size.
TEST_F(CollectionTest, CanIncreaseVectorSizeByResizing)
{
    // Add entries then resize to a larger size.
    add_entries(10);
    size_t initialSize = collection->size();

    collection->resize(15);

    // New size must be greater than the initial size.
    ASSERT_GT(collection->size(), initialSize);
}


// Verify that resizing to a smaller size decreases or bounds the collection size.
TEST_F(CollectionTest, CanDecreaseVectorSizeByResizing)
{
    // Add entries then resize to a smaller size.
    add_entries(10);
    size_t initialSize = collection->size();

    collection->resize(5);

    // New size must be less than or equal to the initial size.
    ASSERT_LE(collection->size(), initialSize);
}


// Verify that resizing to zero results in an empty collection.
TEST_F(CollectionTest, CanResizeVectorToZero)
{
    // Add entries then resize to zero.
    add_entries(10);
    ASSERT_NE(collection->size(), 0);

    collection->resize(0);

    // Collection must be empty.
    ASSERT_EQ(collection->size(), 0);
}


// Verify that clear() erases all elements from the collection.
TEST_F(CollectionTest, CanClearVector)
{
    // Add entries then clear the collection.
    add_entries(10);
    ASSERT_NE(collection->size(), 0);

    collection->clear();

    // Collection must be empty after clear().
    ASSERT_EQ(collection->size(), 0);
}


// Verify that erase(begin, end) removes all elements from the collection.
TEST_F(CollectionTest, CanEraseVectorBeginningToEnd)
{
    // Add entries then erase the full range.
    add_entries(15);
    ASSERT_NE(collection->size(), 0);

    collection->erase(collection->begin(), collection->end());

    // Collection must be empty after erase.
    ASSERT_EQ(collection->size(), 0);
}


// Verify that reserve() increases capacity without changing size.
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize)
{
    // Record initial size and capacity.
    size_t initialSize = collection->size();
    size_t initialCapacity = collection->capacity();

    collection->reserve(50);

    // Size must be unchanged; capacity should increase.
    ASSERT_EQ(initialSize, collection->size());
    EXPECT_LT(initialCapacity, collection->capacity());
}


// Verify that at() throws std::out_of_range for an out-of-bounds index (edge case).
TEST_F(CollectionTest, AtThrowsOutOfRange)
{
    // Request an index just past the end and verify exception is thrown.
    size_t vSize = collection->size();
    ASSERT_THROW(collection->at(vSize + 1), std::out_of_range);
}


// Positive test: adding entries should cause reallocation when capacity is exceeded.
TEST_F(CollectionTest, AddEntriesCausesReallocationWhenExceedCapacity)
{
    // Ensure vector is empty and reserve a small capacity.
    ASSERT_EQ(collection->size(), 0);
    collection->reserve(2);

    // Add entries to fill capacity.
    add_entries(2);

    // Capture address before exceeding capacity.
    const int* before = &collection->front();

    // Add more entries to force reallocation.
    add_entries(10);

    // Capture address after reallocation and verify it changed.
    const int* after = &collection->front();
    ASSERT_NE(before, after);
}


// Negative/edge-case test: erasing an empty range is a no-op and must not throw exception.
TEST_F(CollectionTest, EraseEmptyVectorIsNoOp)
{
    // Start empty.
    ASSERT_EQ(collection->size(), 0);
    const auto initialCapacity = collection->capacity();

    // Erase empty range: should not throw exception and should return end().
    auto it = collection->erase(collection->begin(), collection->end());
    EXPECT_EQ(it, collection->end());

    // No change to size or capacity.
    EXPECT_EQ(collection->size(), 0);
    EXPECT_EQ(collection->capacity(), initialCapacity);

    // begin() equals end() for empty container.
    EXPECT_EQ(collection->begin(), collection->end());
}

// Tests for the secure coding policy presentation
// These tests use the collection to highlight coding 
// Standards from the secure coding policy

// Negative: expects exception (secure behavior)
TEST_F(CollectionTest, Does_vector_at_throw_out_of_range_on_invalid_index)
{
    add_entries(5);  // fill with 5 elements (indices 0-4)
    size_t invalid_index = collection->size();  // == 5 -> out of bounds

    ASSERT_THROW(collection->at(invalid_index), std::out_of_range);
    // Policy benefit: at() enforces bounds -> prevents buffer overflow / invalid read
}

// Positive: valid access succeeds
TEST_F(CollectionTest, Does_vector_at_allow_valid_access_without_throwing)
{
    add_entries(3);  // indices 0-2
    ASSERT_NO_THROW(collection->at(1));          // valid
    EXPECT_EQ(collection->at(1), collection->operator[](1));  // same value
}

// Positive: operator[] works when in bounds
TEST_F(CollectionTest, Can_operator_access_elements_within_bounds_without_issues)
{
    add_entries(4);
    EXPECT_NO_FATAL_FAILURE(collection->operator[](2));  // no crash expected
    EXPECT_EQ(collection->operator[](0), collection->at(0));  // consistent
}

// Negative: demonstrate risk of operator[] (UB warning)
TEST_F(CollectionTest, Does_operator_on_out_of_bounds_index_lead_to_undefined_behavior)
{
    add_entries(1);  // only index 0 valid
    size_t invalid = 10;

    // WARNING: This is deliberately unsafe -> UB in real run
    // In practice: run with -fsanitize=address to catch
    // Here we run in Debugger because it performs a safety check 
    EXPECT_DEBUG_DEATH(collection->operator[](invalid), ".*");  // optional: if using death test
    // Or comment: "Unsafe - may crash, read garbage, or allow exploits (violates STD-003)"
}
