package br.com.romulocsr.biblia1911

import android.app.AlertDialog
import android.content.ClipData
import android.content.ClipboardManager
import android.content.Context
import android.content.Intent
import android.content.res.AssetManager
import android.net.Uri
import android.os.Bundle
import android.util.TypedValue
import android.widget.Button
import android.widget.ScrollView
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    private var testamentoAtual = 1   // 1 = Antigo Testamento, 2 = Novo Testamento
    private var indiceLivroAtual = 0  // 0 = Gênesis (ou Mateus no NT)
    private var capituloAtual = 1     // 1..N
    private var tamanhoFonteSp = 18f

    private lateinit var tvTituloCapitulo: TextView
    private lateinit var tvTextoBiblico: TextView
    private lateinit var scrollLeitura: ScrollView
    private lateinit var btnTestamento: Button
    private lateinit var btnLivro: Button
    private lateinit var btnCapitulo: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        supportActionBar?.hide()
        setContentView(R.layout.activity_main)

        tvTituloCapitulo = findViewById(R.id.tvTituloCapitulo)
        tvTextoBiblico = findViewById(R.id.tvTextoBiblico)
        scrollLeitura = findViewById(R.id.scrollLeitura)
        btnTestamento = findViewById(R.id.btnTestamento)
        btnLivro = findViewById(R.id.btnLivro)
        btnCapitulo = findViewById(R.id.btnCapitulo)

        val btnSobre: Button = findViewById(R.id.btnSobre)
        val btnAnterior: Button = findViewById(R.id.btnAnterior)
        val btnProximo: Button = findViewById(R.id.btnProximo)
        val btnFonteMenor: Button = findViewById(R.id.btnFonteMenor)
        val btnFonteMaior: Button = findViewById(R.id.btnFonteMaior)
        val btnCompartilhar: Button = findViewById(R.id.btnCompartilhar)

        btnSobre.setOnClickListener {
            val mensagem = "Bíblia Almeida ARC-1911\n" +
                    "Atualização ortográfica e gramatical • Edição 11/2026\n\n" +
                    "• Funcionamento 100% offline com os 66 livros.\n" +
                    "• Motor nativo de alta velocidade em linguagem C.\n\n" +
                    "Projeto aberto e contribuições:\n" +
                    "github.com/RomuloCSR"

            AlertDialog.Builder(this)
                .setTitle("Sobre o Projeto")
                .setMessage(mensagem)
                .setPositiveButton("Abrir GitHub") { _, _ ->
                    val intent = Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/RomuloCSR"))
                    startActivity(intent)
                }
                .setNeutralButton("Copiar Link") { _, _ ->
                    val clipboard = getSystemService(Context.CLIPBOARD_SERVICE) as ClipboardManager
                    clipboard.setPrimaryClip(ClipData.newPlainText("GitHub", "https://github.com/RomuloCSR"))
                    Toast.makeText(this, "Link copiado: github.com/RomuloCSR", Toast.LENGTH_SHORT).show()
                }
                .setNegativeButton("Fechar", null)
                .show()
        }

        btnTestamento.setOnClickListener {
            testamentoAtual = if (testamentoAtual == 1) 2 else 1
            indiceLivroAtual = 0
            capituloAtual = 1
            atualizarLeitura()
        }

        btnLivro.setOnClickListener {
            val livros = obterListaLivrosJNI(testamentoAtual)
            val tituloDialogo = if (testamentoAtual == 1) "Antigo Testamento" else "Novo Testamento"
            AlertDialog.Builder(this)
                .setTitle(tituloDialogo)
                .setItems(livros) { _, which ->
                    indiceLivroAtual = which
                    capituloAtual = 1
                    atualizarLeitura()
                }
                .show()
        }

        btnCapitulo.setOnClickListener {
            val totalCaps = obterTotalCapitulosJNI(testamentoAtual, indiceLivroAtual)
            val listaCaps = Array(totalCaps) { i -> "Capítulo ${i + 1}" }
            val livros = obterListaLivrosJNI(testamentoAtual)
            AlertDialog.Builder(this)
                .setTitle(livros[indiceLivroAtual])
                .setItems(listaCaps) { _, which ->
                    capituloAtual = which + 1
                    atualizarLeitura()
                }
                .show()
        }

        btnAnterior.setOnClickListener {
            if (capituloAtual > 1) {
                capituloAtual--
                atualizarLeitura()
            } else if (indiceLivroAtual > 0) {
                indiceLivroAtual--
                capituloAtual = obterTotalCapitulosJNI(testamentoAtual, indiceLivroAtual)
                atualizarLeitura()
            } else if (testamentoAtual == 2) {
                testamentoAtual = 1
                indiceLivroAtual = 38
                capituloAtual = obterTotalCapitulosJNI(1, 38)
                atualizarLeitura()
            }
        }

        btnProximo.setOnClickListener {
            val totalCaps = obterTotalCapitulosJNI(testamentoAtual, indiceLivroAtual)
            if (capituloAtual < totalCaps) {
                capituloAtual++
                atualizarLeitura()
            } else {
                val totalLivros = if (testamentoAtual == 1) 39 else 27
                if (indiceLivroAtual + 1 < totalLivros) {
                    indiceLivroAtual++
                    capituloAtual = 1
                    atualizarLeitura()
                } else if (testamentoAtual == 1) {
                    testamentoAtual = 2
                    indiceLivroAtual = 0
                    capituloAtual = 1
                    atualizarLeitura()
                }
            }
        }

        btnFonteMenor.setOnClickListener {
            if (tamanhoFonteSp > 12f) {
                tamanhoFonteSp -= 2f
                tvTextoBiblico.setTextSize(TypedValue.COMPLEX_UNIT_SP, tamanhoFonteSp)
            }
        }

        btnFonteMaior.setOnClickListener {
            if (tamanhoFonteSp < 32f) {
                tamanhoFonteSp += 2f
                tvTextoBiblico.setTextSize(TypedValue.COMPLEX_UNIT_SP, tamanhoFonteSp)
            }
        }

        btnCompartilhar.setOnClickListener {
            val assinatura = "—\n" +
                    "Bíblia Almeida ARC-1911\n" +
                    "Atualização ortográfica e gramatical • Edição 11/2026\n" +
                    "Projeto aberto: https://github.com/RomuloCSR"
            val textoParaEnviar = "${tvTituloCapitulo.text}\n\n${tvTextoBiblico.text}$assinatura"
            val intent = Intent(Intent.ACTION_SEND).apply {
                type = "text/plain"
                putExtra(Intent.EXTRA_SUBJECT, "${tvTituloCapitulo.text} - Bíblia Almeida ARC-1911")
                putExtra(Intent.EXTRA_TEXT, textoParaEnviar)
            }
            startActivity(Intent.createChooser(intent, "Compartilhar capítulo"))
        }

        atualizarLeitura()
    }

    private fun atualizarLeitura() {
        val livros = obterListaLivrosJNI(testamentoAtual)
        val nomeLivro = if (indiceLivroAtual in livros.indices) livros[indiceLivroAtual] else "Livro"

        btnTestamento.text = if (testamentoAtual == 1) "AT" else "NT"
        btnLivro.text = nomeLivro
        btnCapitulo.text = "Cap. $capituloAtual"
        tvTituloCapitulo.text = "$nomeLivro • Capítulo $capituloAtual"

        val texto = lerCapituloJNI(assets, testamentoAtual, indiceLivroAtual, capituloAtual)
        tvTextoBiblico.text = texto
        scrollLeitura.scrollTo(0, 0)
    }

    external fun obterListaLivrosJNI(testamento: Int): Array<String>
    external fun obterTotalCapitulosJNI(testamento: Int, indiceLivro: Int): Int
    external fun lerCapituloJNI(
        assetManager: AssetManager,
        testamento: Int,
        indiceLivro: Int,
        capitulo: Int
    ): String

    companion object {
        init {
            System.loadLibrary("biblia1911")
        }
    }
}
