function net2other( net , fileName, mode )
%NET2PY Prints into C or Python syntax bias, weight and nodes of a neural
%network
%Usage: mode 'p' for python, any other for 'c'
%Developed by Dhiana Deva
%Contact: dhiana.deva@gmail.com

file=fopen(fileName,'w');

if(mode=='p'),
	fprintf(file, 'NodesVector=[');
else
	fprintf(file, 'const unsigned int NODESVECTOR[]= { ');
end;

%Getting nNodes params:
nNodes(1,1)=net.inputs{1}.size;
fprintf(file, '%i',nNodes(1,1));
for i=1:net.numLayers,
    nNodes(i+1,1)=net.layers{i}.size;
    fprintf(file, ',%i',nNodes(i+1,1));
end;

if(mode=='p')
	fprintf(file, '] \n');
else
	fprintf(file, '}; \n');
end;
	
%Calculating weight vector size:
sumWeights=0;
for i=1:net.numLayers,
    sumWeights=sumWeights+nNodes(i,1)*nNodes(i+1,1);
end;

%Calculating bias vector size:
sumBias=0;
for i=1:net.numLayers,
	sumBias=sumBias+nNodes(i+1,1);
end;

%Calculating input weight vector size:
sumInputWeights=nNodes(1,1)*nNodes(2,1);

%Getting Weight params:
%Obs: Ordered by layer first, then by target node(next layer), then by all
%previous nodes(current layer) who connects to the target.

%Getting input weight params:
if(mode=='p')
	fprintf(file, 'WeightVector=[');
else
	fprintf(file, 'const float WEIGTHVECTOR[]={');
end;

weights = reshape (net.iw{1}',1,[]);
%Getting layers weight params:
for i=2:net.numLayers,
    weightsTest = horzcat(weights,reshape(net.lw{i}',1,[]));
end;

%Printing weight values:
w=size(weightsTest);
fprintf(file, '%.15e',weightsTest(1,1));
for i=2:w(1,2),
    fprintf(file, ',%.15e',weightsTest(1,i));
end;

if (mode=='p');
	fprintf(file, '] \n');
else
	fprintf(file, '}; \n');
end;
	
%Getting bias param:
if (mode=='p')
	fprintf(file, 'BiasVector=[');
else
	fprintf(file, 'const float BIASVECTOR[]={');
end;
	
bias=[];
for i=1:net.numLayers,
    bias=vertcat(bias,net.b{i});
end;

%Printing bias values:
b=size(bias);
fprintf(file, '%.15e',bias(1,1));
for i=2:b(1,1),
    fprintf(file, ',%.15e',bias(i,1));
end;

if(mode=='p')
	fprintf(file, '] \n');
else
	fprintf(file, '}; \n');
end;
	
fclose(file);
