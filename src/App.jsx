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
  const [error, setError] = useState(null);

  const handleOptimize = async () => {
    setIsOptimizing(true);
    setError(null);
    
    try {
      const response = await fetch('http://localhost:3000/api/optimize', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ code }),
      });

      if (!response.ok) {
        const errorData = await response.json();
        throw new Error(errorData.error || 'Optimization failed');
      }

      const data = await response.json();
      setOptimizedCode(data.optimizedCode);
    } catch (error) {
      console.error('Optimization error:', error);
      setError(error.message);
      setOptimizedCode('');
    } finally {
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

        {error && (
          <div className="mt-4 p-4 bg-red-100 border border-red-400 text-red-700 rounded-lg">
            {error}
          </div>
        )}

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