// 题目：900. RLE 迭代器（RLE Iterator）
// 核心思路：下标 i 指向当前段的计数字段，j 记录该段已消耗数量，next 时按需跨段推进。
// 时间复杂度：next 均摊 O(1)，单次最坏 O(n)；空间复杂度：O(n) 保存编码数组。
class RLEIterator {  // 行程长度编码迭代器
public:  // 构造函数与 next 方法对外可见
    RLEIterator(vector<int>& encoding) {  // encoding：交替存放「次数、数值」的数组
        this->encoding = encoding;  // 保存一份编码数组，供后续 next 使用
    }

    int next(int n) {  // 消耗 n 个元素，返回最后一个被消耗的元素值
        while (i < encoding.size()) {  // 还有段没被消耗完就继续找
            if (encoding[i] - j < n) {  // 当前段剩余数量不够本次消耗
                n -= (encoding[i] - j);  // 先把当前段剩余的全部消耗掉
                i += 2;  // 跳过计数字段，指向下一个数值段
                j = 0;  // 新段从 0 开始计已消耗数量
            } else {  // 当前段剩余数量足够
                j += n;  // 在本段内前移 n 个位置
                return encoding[i + 1];  // 返回本段对应的数值
            }
        }
        return -1;  // 所有段都耗尽，按题意返回 -1
    }

private:  // 以下为内部状态
    vector<int> encoding;  // 行程长度编码数组
    int i = 0;  // 当前段计数字段在数组中的下标（偶数位）
    int j = 0;  // 当前段内已经消耗的元素个数
};

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator* obj = new RLEIterator(encoding);
 * int param_1 = obj->next(n);
 */