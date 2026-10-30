// 题目：41. 缺失的第一个正数（First Missing Positive）
// 思路：原地哈希——把每个落在 [1, n] 内的数交换到下标 v-1 上；再从头扫一遍，第一个 nums[i] != i+1 的下标 i 就对应答案 i+1，全部对得上则答案是 n+1。
// 时间复杂度：O(n)，每个数最多被交换常数次；空间复杂度：O(1)，只用了几个临时变量。
int firstMissingPositive(int* nums, int numsSize) {  // nums 是整数数组，numsSize 是它的长度；返回数组中缺失的最小正整数
    for (int i = 0; i < numsSize; ++i) {  // 第一趟：逐格处理，把每个在 [1, n] 内的数交换到它「应该在」的下标上
        while (nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[nums[i] - 1]) {  // 当前数在 [1, n] 内、且还没待在自己的位置上时继续换；用 while 是因为换过来的新值可能也要继续挪
            int j = nums[i] - 1;  // 目标下标：数值 v 应该放在 v-1 处
            int t = nums[i];  // 先暂存当前值，避免交换时被覆盖
            nums[i] = nums[j];  // 把目标位置上的值写到当前坑位
            nums[j] = t;  // 再把暂存的值放进目标位置，完成一次交换
        }  // while 结束（当前位置已经不需要再挪）
    }  // 第一趟结束，此时所有 1..n 范围内的数都尽量回到了自己的位置
    for (int i = 0; i < numsSize; ++i) {  // 第二趟：从左到右找第一个「位不配值」的位置
        if (nums[i] != i + 1) {  // 位置 i 上本应是 i+1，不相等就说明 i+1 缺失
            return i + 1;  // 第一个不匹配的位置对应的数就是缺失的最小正整数
        }  // if 分支结束
    }  // 第二趟结束
    return numsSize + 1;  // 1..n 全部到位，说明缺失的最小正整数只能是 n+1
}  // 函数结束
