// 题目：1800. 最大升序子数组和（Maximum Ascending Subarray Sum）
// 思路：一次遍历，用 sum 维护当前严格升序段的元素和，升序中断时用 max 更新答案并从当前元素重新起段。
// 时间复杂度：O(n)，每个元素只访问一次；空间复杂度：O(1)，只用常数个变量。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏定义：取 a、b 中较大的一个，避免函数调用开销

// 入口函数：nums 为数组首地址，numsSize 为长度，返回最大升序子数组的元素和
int maxAscendingSum(int* nums, int numsSize) {
    int res = nums[0];  // res 记录目前见到过的最大升序段和，先用第一个元素初始化
    int sum = nums[0];  // sum 维护「当前」这段升序子数组的和，同样从第一个元素起步
    for (int i = 1; i < numsSize; i++) {  // 从下标 1 开始遍历，每次与前一个元素比较
        if (nums[i - 1] >= nums[i]) {  // 前一个元素 >= 当前元素：严格升序被打断，当前段到此结束
            res = max(res, sum);  // 用刚结束的这段和去刷新历史最大值
            sum = 0;  // 清零，准备把后面的元素累加成新的一段
        }
        sum += nums[i];  // 把当前元素计入当前升序段的和
    }
    return max(res, sum);  // 收尾：最后一段没被中断，也要参与比较后再返回最大值
}