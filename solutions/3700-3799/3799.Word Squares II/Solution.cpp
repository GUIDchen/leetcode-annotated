// 题目：3799. 单词方块 II（Word Squares II）
// 思路：单词长度固定为 4，枚举上、左、右、下四条边的单词，只校验四个角上的字符是否两两相等。
// 时间复杂度：O(n^4)，四重循环枚举四条边；空间复杂度：O(1)（不计答案本身占用的空间）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<string>> wordSquares(vector<string>& words) {  // 返回由四个长度为 4 的单词拼成的所有单词方块
        ranges::sort(words);  // 先排序，使答案整体按字典序排列
        int n = words.size();  // 单词总数
        vector<vector<string>> ans;  // 存放所有合法单词方块

        for (int i = 0; i < n; i++) {  // 枚举第 1 行（上边）的单词
            string top = words[i];  // 上边单词
            for (int j = 0; j < n; j++) {  // 枚举第 1 列（左边）的单词
                if (j != i) {  // 同一个单词不能用两次
                    string left = words[j];  // 左边单词
                    for (int k = 0; k < n; k++) {  // 枚举第 3 列（右边）的单词
                        if (k != j && k != i) {  // 不能和已选的 top、left 重复
                            string right = words[k];  // 右边单词
                            for (int h = 0; h < n; h++) {  // 枚举第 4 行（下边）的单词
                                if (h != k && h != j && h != i) {  // 不能与前三个已选单词重复
                                    string bottom = words[h];  // 下边单词
                                    if (top[0] == left[0] && top[3] == right[0] && bottom[0] == left[3] && bottom[3] == right[3]) {  // 四个角上的字符必须两两相等：左上、右上、左下、右下
                                        ans.push_back({top, left, right, bottom});  // 四角匹配，记录这个方块
                                    }  // 结束 if (top[0] == left[0] && top[3] == right[0] && bottom[0] == left[3] && bottom[3] == right[3])
                                }  // 结束 if (h != k && h != j && h != i)
                            }  // 结束 for (int h = 0; h < n; h++)
                        }  // 结束 if (k != j && k != i)
                    }  // 结束 for (int k = 0; k < n; k++)
                }  // 结束 if (j != i)
            }  // 结束 for (int j = 0; j < n; j++)
        }  // 结束 for (int i = 0; i < n; i++)
        return ans;  // 返回全部合法方块
    }  // 结束 vector<vector<string>> wordSquares(vector<string>& words)
};  // 结束 class Solution
