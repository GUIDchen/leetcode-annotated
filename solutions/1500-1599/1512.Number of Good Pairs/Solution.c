// 题目：1512. 好数对的数目（Number of Good Pairs）
// 思路：一次遍历计数：当前元素与「之前出现过的同值元素」都能组成好数对，把旧计数累加进答案。
// 时间复杂度：O(n)，每个元素常数次操作；空间复杂度：O(1)，计数数组大小固定 101。
int numIdenticalPairs(int* nums, int numsSize) {  // nums：输入数组；numsSize：数组长度；返回满足 i<j 且 nums[i]==nums[j] 的下标对数
    int cnt[101] = {0};  // cnt[v]：值 v 到目前为止出现过的次数；题目保证 1 <= nums[i] <= 100 故开 101 个桶
    int ans = 0;  // ans：累计的好数对数目
    for (int i = 0; i < numsSize; i++) {  // 从左到右扫描每个元素
        ans += cnt[nums[i]]++;  // 后自增先返回旧值：旧值就是此前与当前值相同的元素个数，也就是新增的好数对数量
    }  // 结束遍历
    return ans;  // 返回好数对总数
}  // 结束函数