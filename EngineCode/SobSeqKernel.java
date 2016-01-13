/**
 * Document: MaxCompiler Tutorial (maxcompiler-tutorial.pdf))>
 * Chapter: 9      Example: 3      Name: Complex Counter
 * MaxFile name: ComplexCounter
 * Summary:
 *       Kernel design that creates advanced counters specifying
 *   maximum value, increment, wrap mode and enable streams.
 */

package complexcounter;

import com.maxeler.maxcompiler.v2.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v2.kernelcompiler.KernelParameters;
import com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.core.Count;
import com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.core.Count.Counter;
import com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.core.Count.WrapMode;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEVar;

class ComplexCounterKernel extends Kernel {

	private static final int width = 32;

	ComplexCounterKernel(KernelParameters parameters,
		int countOneMax, int countOneInc, int countTwoMax) {
		super(parameters);

		// Input
		DFEVar streamIn = io.input("input", dfeUInt(width));

		// Counters and calculation
		Count.Params paramsOne = control.count.makeParams(width)
			.withMax(countOneMax)
			.withInc(countOneInc);

		Counter counterOne = control.count.makeCounter(paramsOne);

		Count.Params paramsTwo = control.count.makeParams(width)
			.withEnable(counterOne.getWrap())
			.withMax(countTwoMax)
			.withWrapMode(WrapMode.STOP_AT_MAX);

		Counter counterTwo = control.count.makeCounter(paramsTwo);

		DFEVar countTwo = counterTwo.getCount();
		DFEVar countOne = counterOne.getCount();

		DFEVar result = streamIn + countTwo;

		// Output
		io.output("result", result, dfeUInt(width));
		io.output("countOne", countOne, countOne.getType());
		io.output("countTwo", countTwo, countTwo.getType());
	}
}

