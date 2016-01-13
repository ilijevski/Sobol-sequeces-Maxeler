/**
 * Document: MaxCompiler Tutorial (maxcompiler-tutorial.pdf))>
 * Chapter: 9      Example: 3      Name: Complex Counter
 * MaxFile name: ComplexCounter
 * Summary:
 *        Manager for an advanced counter kernel design.
 *   All IO is between the CPU and the DFE.
 */

package complexcounter;

import com.maxeler.maxcompiler.v2.build.EngineParameters;
import com.maxeler.maxcompiler.v2.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v2.managers.standard.Manager;
import com.maxeler.maxcompiler.v2.managers.standard.Manager.IOType;

class ComplexCounterManager {

	private static final int countOneMax = 8;
	private static final int countOneInc = 2;
	private static final int countTwoMax = 5;

	public static void main(String[] args) {
		Manager m = new Manager(new EngineParameters(args));
		Kernel k = new ComplexCounterKernel(m.makeKernelParameters(),
				countOneMax, countOneInc, countTwoMax);
		m.setKernel(k);
		m.addMaxFileConstant("countOneMax", countOneMax);
		m.addMaxFileConstant("countOneInc", countOneInc);
		m.addMaxFileConstant("countTwoMax", countTwoMax);
		m.setIO(IOType.ALL_CPU);
		m.createSLiCinterface();
		m.build();
	}
}
