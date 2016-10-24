using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tester
{
    public class Player
    {
        public long id;
        public long score;
        public long oldScore;

        public Player(long id, long score)
        {
            this.id = id;
            this.score = score;
            this.oldScore = score;
        }
        public void SetScore(long score)
        {
            if (this.score != score)
            {
                this.oldScore = this.score;
                this.score = score;
            }
        }
    };

    class Program
    {
        static void Main(string[] args)
        {
            var ps = new List<Player>();
            ps.Add(new Player(1, 100));
            ps.Add(new Player(2, 200));
            ps.Add(new Player(3, 200));
            ps.Add(new Player(4, 300));

            using (var r = new xxlib.Ranker())
            {
                foreach (var p in ps) r.Add(p.id, p.score);
                foreach (var p in ps) Console.WriteLine(r.GetRank(p.score));
                Console.WriteLine();
                {
                    var p = ps[1];
                    p.SetScore(400);
                    r.Update(p.id, p.oldScore, p.score);

                    var n = 3;
                    var ranks = new int[3];
                    var ids = new long[3];
                    n = r.FillRanks(p.id, p.score, n, ids, ranks);
                    for (int i = 0; i < n; i++)
                    {
                        Console.WriteLine("id = " + ids[i] + ", ranks = " + ranks[i]);
                    }
                }
            }
        }
    }
}
