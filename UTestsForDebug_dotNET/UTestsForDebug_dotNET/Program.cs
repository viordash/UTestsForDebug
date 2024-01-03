namespace UTestsForDebug_dotNET {
    internal class Program {
        static void Main(string[] args) {
            Console.WriteLine("Super calc");
            Console.WriteLine("Enter number: ");
            var input = Console.ReadLine();
            if(!int.TryParse(input, out int number)) {
                Console.WriteLine("Not a number");
            }

            Console.WriteLine($"Super value is {SuperCalc.GetVeryDifficultCompute(number)}");
        }
    }
}
