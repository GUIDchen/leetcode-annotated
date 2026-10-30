// 题目：2554. 从一个范围内选择最多整数 I（Maximum Number of Integers to Choose From a Range I）
// 思路：贪心——先把禁用数组排序，然后从 1 到 n 顺序枚举，能选就选（选最小的数最划算）；被禁用就用指针顺序跳过，一旦加上当前数会超过 maxSum 就停止。
// 时间复杂度：O(bannedSize log bannedSize + n)，排序加一次线性枚举；空间复杂度：O(1)，除排序外只用常数个变量（原地排序）。
int cmp(const void* a, const void* b) {  // qsort 需要的比较函数：按升序比较两个 int
    return *(int*) a - *(int*) b;  // 返回负值表示 a 排在 b 前面，正值则相反
}  // cmp 函数结束

int maxCount(int* banned, int bannedSize, int n, int maxSum) {  // banned 是禁用数字，bannedSize 是它的长度；n 是范围上界，maxSum 是所选数字之和的上限
    qsort(banned, bannedSize, sizeof(int), cmp);  // 先给禁用数组排序，后面才能用一个指针顺序跳过禁用值
    int sum = 0;  // sum 记录当前已选数字的总和
    int ans = 0;  // ans 记录已经选了多少个数字
    for (int i = 1, j = 0; i <= n; i++) {  // i 枚举 1..n；j 指向 banned 中第一个不小于 i 的位置
        if (sum + i > maxSum) {  // 贪心：再加上 i 就超限；因为 i 递增，后面只会更大
            break;  // 直接结束枚举
        }  // 超限判断结束
        if (j < bannedSize && i == banned[j]) {  // 当前数字 i 出现在禁用数组中
            while (j < bannedSize && i == banned[j]) {  // 跳过 banned 中所有等于 i 的重复元素
                j++;  // 指针后移
            }  // 去重跳过结束
        } else {  // 当前数字没有被禁用，可以选取
            sum += i;  // 累加到已选总和
            ans++;  // 选取个数加一
        }  // 分支结束
    }  // 枚举结束
    return ans;  // 返回最多能选的整数个数
}  // maxCount 函数结束