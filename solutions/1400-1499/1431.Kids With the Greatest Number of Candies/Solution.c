// 题目：1431. 拥有最多糖果的孩子（Kids With the Greatest Number of Candies）
// 思路：先求原有糖果数的最大值，再逐个判断「加上额外糖果后是否不小于该最大值」。
// 时间复杂度：O(n)，两遍扫描；空间复杂度：O(n)，存放返回的 bool 数组。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 手写取最大值的宏；每个参数都加括号，避免表达式展开后的优先级错误
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize) {  // candies：每个孩子已有的糖果数；extraCandies：可额外给的糖果数；*returnSize 输出结果长度
    int mx = 0;  // 记录当前最大值，初始为 0（糖果数非负）
    for (int i = 0; i < candiesSize; i++) {  // 第一遍扫描：找出所有孩子中糖果数的最大值
        mx = max(mx, candies[i]);  // 逐个比较并更新最大值
    }  // 第一遍扫描结束
    bool* ans = malloc(candiesSize * sizeof(bool));  // 为返回数组分配内存：题目约定由调用方负责 free
    for (int i = 0; i < candiesSize; i++) {  // 第二遍扫描：逐个判断该孩子能否达到最大值
        ans[i] = candies[i] + extraCandies >= mx;  // 加上额外糖果后不小于原最大值，则该孩子可以并列最多
    }  // 第二遍扫描结束
    *returnSize = candiesSize;  // 返回数组长度等于孩子个数
    return ans;  // 返回 malloc 出来的结果数组
}  // 函数结束