// 题目：1561. 你可以获得的最大硬币数目（Maximum Number of Coins You Can Get）
// 思路：把硬币堆升序排序，最小的三分之一归对手，剩下的按「最小给对手、中间给自己、最大给朋友」三堆一组，自己取每组的中位数。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，除排序外只用常数个变量（原地排序）。
int compare(const void* a, const void* b) {  // qsort 要求的比较函数：a、b 指向两个待比较的 int
    return (*(int*) a - *(int*) b);  // 升序规则：a 小而返回负数，相等返回 0，a 大返回正数
}  // 比较函数结束

int maxCoins(int* piles, int pilesSize) {  // piles：每堆硬币数；pilesSize：堆数；返回自己能拿到的最多硬币
    qsort(piles, pilesSize, sizeof(int), compare);  // 先按硬币数升序原地排序，方便按大小分组
    int ans = 0;  // 自己最终能拿到的硬币总数
    for (int i = pilesSize / 3; i < pilesSize; i += 2) {  // 最小的三分之一让给对手；此后每两堆取下标较小者即该组的中位数
        ans += piles[i];  // 累加属于自己的一堆
    }  // 循环体结束
    return ans;  // 返回最大收益
}  // 函数结束
