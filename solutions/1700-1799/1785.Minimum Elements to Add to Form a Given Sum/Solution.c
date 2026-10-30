// 题目：1785. 构成特定和需要添加的最少元素（Minimum Elements to Add to Form a Given Sum）
// 思路：先求出数组和与目标值 goal 的差值，每个元素绝对值不超过 limit，所以最少个数就是差值的向上取整。
// 时间复杂度：O(n)，一次遍历求和；空间复杂度：O(1)，只用到常数个变量。
int minElements(int* nums, int numsSize, int limit, int goal) {  // nums 是原数组，numsSize 是长度，limit 是每个可加元素的绝对值上限，goal 是目标和
    long long sum = 0;  // 用 64 位累加，避免 n * nums[i] 溢出
    for (int i = 0; i < numsSize; i++) {  // 遍历数组求当前和
        sum += nums[i];  // 累加第 i 个元素
    }
    long long diff = labs(goal - sum);  // 还差的绝对值；labs 处理 long long，防止 int 溢出
    return (diff + limit - 1) / limit;  // 向上取整：每个元素最多补 limit，整除写法避免浮点误差
}