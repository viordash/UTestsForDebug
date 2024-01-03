using static System.Runtime.InteropServices.JavaScript.JSType;

namespace UTestsForDebug_dotNET.Tests {
    public class SuperCalcTests {
        [SetUp]
        public void Setup() {
        }

        [Test]
        public void GetVeryDifficultCompute_Test() {
            var value = SuperCalc.GetVeryDifficultCompute(0);
            Assert.That(value, Is.EqualTo(0));

            value = SuperCalc.GetVeryDifficultCompute(int.MaxValue);
            Assert.That(value, Is.EqualTo(4.6116860143471688E+18).Within(1).Ulps);

            value = SuperCalc.GetVeryDifficultCompute(int.MinValue);
            Assert.That(value, Is.EqualTo(4.61168601821264E+18).Within(1).Ulps);
        }
    }
}