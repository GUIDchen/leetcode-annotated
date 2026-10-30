// 题目：976. 三角形的最大周长（Largest Perimeter Triangle）
// 思路：降序排序后从最大的三条边开始尝试，一旦满足「两短边之和大于最长边」即为最大周长。
// 时间复杂度：O(n log n)，来自排序；空间复杂度：O(1)，只用了常数级额外变量。
int cmp(const void* a, const void* b) {  // qsort 的比较函数：按数值从大到小排序
    return *(int*) b - *(int*) a;  // 降序写法：后一个减前一个，使大数排在前面
}  // 比较函数结束

int largestPerimeter(int* nums, int numsSize) {  // nums：边长数组；numsSize：边长个数，返回能组成的最大三角形周长
    qsort(nums, numsSize, sizeof(int), cmp);  // 先降序排序，方便从最大的三条边开始尝试
    for (int i = 2; i < numsSize; i++) {  // i 指向当前候选的最长边，从末尾往前扫
        if (nums[i - 2] < nums[i - 1] + nums[i]) {  // 三角形判定：两条较短边之和必须严格大于最长边
            return nums[i - 2] + nums[i - 1] + nums[i];  // 满足就返回这三条边的周长；因为已降序，首次命中即为最大周长
        }  // if 结束
    }  // for 循环结束
    return 0;  // 不存在能组成三角形的三条边，按题意返回 0
}  // 函数结束