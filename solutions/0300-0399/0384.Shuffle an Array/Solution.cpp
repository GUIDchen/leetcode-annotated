// 题目：384. 打乱数组（Shuffle an Array）
// 思路：构造时保存原始数组副本；shuffle 用 Fisher-Yates 洗牌，第 i 位与 [i, n-1] 中的随机位置交换。
// 时间复杂度：reset 为 O(n)，shuffle 为 O(n)；空间复杂度：O(n)，额外保存一份原始数组。
class Solution {  // 题解类，判题器会交替调用 reset 与 shuffle
public:  // 对外接口
    vector<int> nums;  // 当前（可能已被打乱）的工作数组
    vector<int> original;  // 原始数组副本，reset 时用来还原

    Solution(vector<int>& nums) {  // 构造函数：nums 是初始数组
        this->nums = nums;  // 拷贝一份作为可变工作数组
        this->original.resize(nums.size());  // 先按原长度分配空间，避免后面的 copy 越界
        copy(nums.begin(), nums.end(), original.begin());  // 把初始排列完整存进 original，作为还原基准
    }

    vector<int> reset() {  // 恢复到初始排列并返回
        copy(original.begin(), original.end(), nums.begin());  // 从副本写回工作数组，长度不变所以不必重新分配
        return nums;  // 返回恢复后的数组
    }

    vector<int> shuffle() {  // 等概率地打乱当前数组并返回
        for (int i = 0; i < nums.size(); ++i) {  // Fisher-Yates：从左到右逐个确定第 i 位放哪个元素
            int j = i + rand() % (nums.size() - i);  // 在 [i, n-1] 中随机挑下标：剩余长度取模后整体右移 i
            swap(nums[i], nums[j]);  // 交换后第 i 位定稿，每个元素落到这里的概率都是 1/(n-i)
        }
        return nums;  // 返回打乱后的数组
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */