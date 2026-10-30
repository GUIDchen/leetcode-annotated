// 题目：2574. 左右元素和的差值（Left and Right Sum Differences）
// 思路：先把整个数组求和作为右侧和，再从左往右移动分界线，边移动边维护左侧和与右侧和。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，用于存放返回数组。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* leftRightDifference(int* nums, int numsSize, int* returnSize) {  // nums 是输入数组，numsSize 是它的长度，returnSize 回传结果长度
    *returnSize = numsSize;  // 结果数组与输入数组等长
    int* ans = (int*) malloc(sizeof(int) * numsSize);  // 申请返回数组的内存，由调用方负责释放

    int l = 0, r = 0;  // l 是当前元素左侧的元素和，r 是右侧的元素和
    for (int i = 0; i < numsSize; ++i) {  // 先遍历一遍，把全部元素累加到右侧和
        r += nums[i];  // 累加当前元素
    }

    for (int i = 0; i < numsSize; ++i) {  // 从左到右依次计算每个位置的差值
        r -= nums[i];  // 当前元素不再算在右侧，先从右侧和中减掉
        ans[i] = abs(l - r);  // 按题目要求保存左右和之差的绝对值
        l += nums[i];  // 当前元素加入左侧和，供下一个位置使用
    }

    return ans;  // 返回结果数组
}
