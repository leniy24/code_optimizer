import express from 'express';
import { exec } from 'child_process';
import fs from 'fs/promises';
import cors from 'cors';
import { fileURLToPath } from 'url';
import { dirname, join } from 'path';
import bodyParser from 'body-parser';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

const app = express();
app.use(cors());
app.use(bodyParser.json());

app.post('/api/optimize', async (req, res) => {
  try {
    const { code } = req.body;
    if (!code) {
      return res.status(400).json({ error: 'No code provided' });
    }

    // Create a temporary input file
    const inputPath = join(__dirname, 'temp_input.c');
    await fs.writeFile(inputPath, code);

    // Path to the optimizer executable
    const optimizerPath = join(__dirname, 'cd-main', 'cd-main', 'build', 'code_optimizer');

    // Execute the C++ optimizer
    exec(`${optimizerPath} ${inputPath}`, async (error, stdout, stderr) => {
      try {
        if (error) {
          console.error('Optimization error:', error);
          return res.status(500).json({ error: 'Optimization failed' });
        }

        // Read the optimized output
        const outputPath = join(__dirname, 'cd-main', 'cd-main', 'output', `optimized_${inputPath.split('/').pop()}`);
        const optimizedCode = await fs.readFile(outputPath, 'utf8');

        // Clean up temporary files
        await fs.unlink(inputPath);

        res.json({ optimizedCode });
      } catch (err) {
        console.error('Error processing optimization:', err);
        res.status(500).json({ error: 'Failed to process optimization' });
      }
    });
  } catch (err) {
    console.error('Server error:', err);
    res.status(500).json({ error: 'Internal server error' });
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});