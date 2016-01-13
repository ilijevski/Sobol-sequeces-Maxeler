package sobseq;

import com.maxeler.maxcompiler.v2.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v2.kernelcompiler.KernelParameters;
import com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.core.Count;
import com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.core.Count.Counter;
import com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.core.Count.WrapMode;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEVar;

class ComplexCounterKernel extends Kernel {

	ComplexCounterKernel(KernelParameters parameters,
		int countOneMax, int countOneInc, int countTwoMax) {
		super(parameters);

		DFEVar ix = io.input("ix", dfeUInt);
		DFEVar iv = io.input("iv", dfeUInt);
		DFEVar fac = io.scalarInput("fac", dfeFloat(8,24));

		/*
			ix[k] ^= iv[im+k];
			x[k] = ix[k] * fac;
		*/
		DFEVar ixOut = ixOut ^ iv; 
		DFEVar x = ix * fac;

		io.output("ixOut", ixOut, dfeUInt);
		io.output("x", x, dfeFloat(8,24));
	}
}

