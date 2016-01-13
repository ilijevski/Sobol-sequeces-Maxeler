package sobseq;

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

		DFEVar ix = io.input("ix", uLong);
		DFEVar iv = io.input("iv", uLong);
		DFEVar fac = io.scalarInput("fac", uFloat);

		/*
			ix[k] ^= iv[im+k];
			x[k] = ix[k] * fac;
		*/
		DFEVar ixOut ^= iv; 
		DFEVar x = ix * fac;

		io.output("ixOut", ixOut, type);
		io.output("x", x, type);
	}
}

