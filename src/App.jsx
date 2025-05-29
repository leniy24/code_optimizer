import React, { useState } from 'react';
import { Editor } from '@monaco-editor/react';

const defaultCode = `int main() {
    int a = 2 + 3;
    int b = 4 + 6;
    int c = a + b;
    return 0;
}`;

function App() {
  const [code, setCode] = useState(defaultCode);
  const [optimizedCode, setOptimizedCode] = useState('');
  const [isOptimizing, setIsOptimizing] = useState(false);

  const handleOptimize = async () => {
    setIsOptimizing(true);
    try {
      // In a real implementation, this would call your C++ optimizer
      // For now, we'll simulate the optimization
      setTimeout(() => {
        const simulated = code.replace(/(\d+)\s*\+\s*(\d+)/g, (_, a, b) => 
          String(Number(a) + Number(b))
        );
        setOptimizedCode(simulated);
        setIsOptimizing(false);
      }, 1000);
    } catch (error) {
      console.error('Optimization failed:', error);
      setIsOptimizing(false);
    }
  };

  return (
    <div className="min-h-screen bg-gray-100 py-8 px-4">
      <div className="max-w-7xl mx-auto">
        <h1 className="text-3xl font-bold text-gray-900 mb-8 text-center">
          Code Optimizer
        </h1>
        
        <div className="grid grid-cols-1 md:grid-cols-2 gap-8">
          <div className="bg-white rounded-lg shadow-lg p-6">
            <h2 className="text-xl font-semibold mb-4">Input Code</h2>
            <div className="h-[500px] border rounded-lg overflow-hidden">
              <Editor
                height="100%"
                defaultLanguage="c"
                value={code}
                onChange={setCode}
                theme="vs-light"
                options={{
                  minimap: { enabled: false },
                  fontSize: 14,
                }}
              />
            </div>
          </div>

          <div className="bg-white rounded-lg shadow-lg p-6">
            <h2 className="text-xl font-semibold mb-4">Optimized Code</h2>
            <div className="h-[500px] border rounded-lg overflow-hidden">
              <Editor
                height="100%"
                defaultLanguage="c"
                value={optimizedCode}
                theme="vs-light"
                options={{
                  readOnly: true,
                  minimap: { enabled: false },
                  fontSize: 14,
                }}
              />
            </div>
          </div>
        </div>

        <div className="mt-8 flex justify-center">
          <button
            onClick={handleOptimize}
            disabled={isOptimizing}
            className={`px-6 py-3 rounded-lg text-white font-semibold ${
              isOptimizing
                ? 'bg-blue-400 cursor-not-allowed'
                : 'bg-blue-600 hover:bg-blue-700'
            }`}
          >
            {isOptimizing ? 'Optimizing...' : 'Optimize Code'}
          </button>
        </div>
      </div>
    </div>
  );
}

export default App;