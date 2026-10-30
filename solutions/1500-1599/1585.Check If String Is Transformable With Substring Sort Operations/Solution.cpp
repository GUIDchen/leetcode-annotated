// 题目：1585. 检查字符串是否可以通过排序子字符串得到另一个字符串（Check If String Is Transformable With Substring Sort Operations）
// 思路：排序子串只会让较小的数字往左移，因此按 t 逐位消费数字时，若有更小的数字还挡在它前面，就永远无法完成。
// 时间复杂度：O(n * 10)，每个字符最多检查 10 个更小的数字；空间复杂度：O(n)，保存各数字的下标队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isTransformable(string s, string t) {  // s 为原串，t 为目标串
        queue<int> pos[10];  // pos[d] 按出现顺序保存数字 d 在 s 中的全部下标
        for (int i = 0; i < s.size(); ++i) {  // 扫描 s，收集每个数字的位置
            pos[s[i] - '0'].push(i);  // 字符转数字后入队，队首即最靠前的可用位置
        }
        for (char& c : t) {  // 按目标串从左到右依次消费数字
            int x = c - '0';  // 当前需要的数字
            if (pos[x].empty()) {  // s 中已没有可用的 x，说明数量不匹配
                return false;  // 直接判定不可变换
            }
            for (int j = 0; j < x; ++j) {  // 检查所有比 x 小的数字 j
                if (!pos[j].empty() && pos[j].front() < pos[x].front()) {  // j 比 x 更靠前地出现
                    return false;  // 排序只能把小的往左移，无法让它越过 x，故不可能
                }
            }
            pos[x].pop();  // x 已经就位，弹出它最靠前的那个位置
        }
        return true;  // 全部数字都消费成功，说明可以变换得到
    }
};